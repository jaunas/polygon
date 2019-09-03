#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "glad/glad.h"

#include "Camera.h"
#include "World.h"

#include "CubesScene.h"
#include "Texture.h"

class Application {
public:
    Application(unsigned int width, unsigned int height)
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
        
        world = new World(width, height);
        
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

            world->render(camera);

            window.display();
        }
    }

private:
    sf::Window window;
    Camera camera;
    World* world;
};

#endif /* APPLICATION_H */

