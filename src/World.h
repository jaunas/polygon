#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "CubesScene.h"

class World {
public:
    World(unsigned int width, unsigned int height)
    {
        sf::Texture texture;
        texture.loadFromFile("Resources/img/terrain.png");
        this->scene.setTexture(texture);
        this->scene.setTextureCoordinates(Cube::Wall::Top, sf::IntRect(32, 144, 16, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Bottom, sf::IntRect(32, 0, 16, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Left, sf::IntRect(48, 0, 16, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Right, sf::IntRect(48, 0, 16, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Back, sf::IntRect(48, 0, 16, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Front, sf::IntRect(48, 0, 16, 16));

        shader.loadFromFile("src/shader/textureShader.vs", "src/shader/textureShader.fs");
        this->scene.setShader(&shader);
        this->scene.loadVertices();

        float ratio = (float)width/(float)height;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
        shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(projection)));
    }
    
    virtual ~World()
    {
    }
    
    void render(Camera camera)
    {
        view = camera.lookAt();

        shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr(view)));

        scene.draw();
    }
private:
    CubesScene scene;
    glm::mat4 view;
    sf::Shader shader;
};

#endif /* WORLD_H */

