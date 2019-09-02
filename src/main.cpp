#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "Texture.h"
#include "CubesScene.h"
#include "Camera.h"
#include "Rectangle.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(
    glm::vec3(0.0f, 0.0f, 3.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    SCR_WIDTH,
    SCR_HEIGHT
);

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 5;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.attributeFlags = sf::ContextSettings::Attribute::Core;

    sf::Window window;
    window.create(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Polygon", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    if (!gladLoadGL()) {
        exit(-1);
    }

    unsigned int viewLocation, projectionLocation;
    
    Shader shader("src/shader/textureShader.vs", "src/shader/textureShader.fs");
    
    viewLocation = glGetUniformLocation(shader.ID, "view");
    projectionLocation = glGetUniformLocation(shader.ID, "projection");    

    Texture texture("Resources/img/terrain.png", GL_RGBA, 16);
    CubesScene containers(
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3( 0.5f, -0.5f,  0.5f),
            glm::vec3( 0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3( 0.5f, -0.5f, -0.5f),
            glm::vec3( 0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f)
    );

    containers.setTexture(texture);
    containers.setTextureCoordinates(Cube::Wall::Top, texture.getCoordinates(3, 7));
    containers.setTextureCoordinates(Cube::Wall::Bottom, texture.getCoordinates(3, 16));
    containers.setTextureCoordinates(Cube::Wall::Left, texture.getCoordinates(4, 16));
    containers.setTextureCoordinates(Cube::Wall::Right, texture.getCoordinates(4, 16));
    containers.setTextureCoordinates(Cube::Wall::Back, texture.getCoordinates(4, 16));
    containers.setTextureCoordinates(Cube::Wall::Front, texture.getCoordinates(4, 16));
    
    containers.setShader(shader);
    containers.loadVertices();

    Rectangle rect(
            glm::vec3(2.0f, -0.5f, 0.0f),
            glm::vec3(3.0f, -0.5f, 0.0f),
            glm::vec3(3.0f, 0.5f, 0.0f),
            glm::vec3(2.0f, 0.5f, 0.0f)
    );

    rect.setTexture(texture);
    rect.setShader(shader);
    rect.setTextureCoordinates(texture.getCoordinates(4,16));
    rect.loadVertices();

    float ratio = (float)SCR_WIDTH/(float)SCR_HEIGHT;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
    
    glm::mat4 view;

    glEnable(GL_DEPTH_TEST);
    
    // render loop
    // -----------
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
        
        camera.processMouseMovement(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = camera.lookAt();

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        
        containers.draw();
        rect.draw();

        window.display();
    }
    
    return 0;
}
