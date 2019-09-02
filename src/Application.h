#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "glad/glad.h"

#include "Camera.h"

#include "CubesScene.h"
#include "Texture.h"
#include "Shader.h"

class Application {
public:
    Application(unsigned int width, unsigned int height, Camera camera, CubesScene scene)
    : camera(camera), scene(scene)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 0;
        settings.majorVersion = 4;
        settings.minorVersion = 5;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.attributeFlags = sf::ContextSettings::Attribute::Core;
        
        window.create(sf::VideoMode(width, height), "Polygon", sf::Style::Close, settings);
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        if (!gladLoadGL()) {
            exit(-1);
        }
        
        
        // Create example world
        Shader shader("src/shader/textureShader.vs", "src/shader/textureShader.fs");
        viewLocation = glGetUniformLocation(shader.ID, "view");
        projectionLocation = glGetUniformLocation(shader.ID, "projection");    
        Texture texture("Resources/img/terrain.png", GL_RGBA, 16);
        this->scene.setTexture(texture);
        this->scene.setTextureCoordinates(Cube::Wall::Top, texture.getCoordinates(3, 7));
        this->scene.setTextureCoordinates(Cube::Wall::Bottom, texture.getCoordinates(3, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Left, texture.getCoordinates(4, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Right, texture.getCoordinates(4, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Back, texture.getCoordinates(4, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Front, texture.getCoordinates(4, 16));

        this->scene.setShader(shader);
        this->scene.loadVertices();

        float ratio = (float)width/(float)height;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

        glEnable(GL_DEPTH_TEST);
    }
    
    virtual ~Application()
    {
    }
    
    void runLoop()
    {
        sf::Time elapsedTime;
        sf::Clock clock;
        while (window.isOpen())
        {
            elapsedTime = clock.restart();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                camera.go(Camera::Direction::LEFT, elapsedTime.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                camera.go(Camera::Direction::FORWARD, elapsedTime.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                camera.go(Camera::Direction::BACKWARD, elapsedTime.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                camera.go(Camera::Direction::RIGHT, elapsedTime.asSeconds());
            }

            camera.processMouseMovement(sf::Mouse::getPosition(window));

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            view = camera.lookAt();

            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

            scene.draw();

            window.display();
        }
    }

    sf::Window window;
    Camera camera;
private:
    CubesScene scene;
    unsigned int viewLocation, projectionLocation;
    glm::mat4 view;
};

#endif /* APPLICATION_H */

