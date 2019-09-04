#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "glad/glad.h"

#include "Camera.h"
#include "World.h"

#include "CubesScene.h"

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
        
        m_window.create(sf::VideoMode(width, height), "Polygon", sf::Style::Close, settings);
        m_window.setVerticalSyncEnabled(true);
        m_window.setActive(true);

        if (!gladLoadGL()) {
            exit(-1);
        }
        
        m_world = new World(width, height);
        
        glEnable(GL_DEPTH_TEST);
    }
    
    virtual ~Application()
    {
    }
    
    void runLoop()
    {
        sf::Time elapsedTime;
        sf::Clock clock;
        while (m_window.isOpen())
        {
            elapsedTime = clock.restart();
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                m_camera.go(Camera::Direction::LEFT, elapsedTime.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                m_camera.go(Camera::Direction::FORWARD, elapsedTime.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                m_camera.go(Camera::Direction::BACKWARD, elapsedTime.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                m_camera.go(Camera::Direction::RIGHT, elapsedTime.asSeconds());
            }

            m_camera.processMouseMovement(sf::Mouse::getPosition(m_window));

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_world->render(m_camera);

            m_window.display();
        }
    }

private:
    sf::Window m_window;
    Camera m_camera;
    World* m_world;
};

#endif /* APPLICATION_H */

