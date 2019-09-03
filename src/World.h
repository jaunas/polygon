#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics/Shader.hpp>

#include "CubesScene.h"

class World {
public:
    World(unsigned int width, unsigned int height)
    {
        Texture texture("Resources/img/terrain.png", GL_RGBA, 16);
        this->scene.setTexture(texture);
        this->scene.setTextureCoordinates(Cube::Wall::Top, texture.getCoordinates(3, 7));
        this->scene.setTextureCoordinates(Cube::Wall::Bottom, texture.getCoordinates(3, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Left, texture.getCoordinates(4, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Right, texture.getCoordinates(4, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Back, texture.getCoordinates(4, 16));
        this->scene.setTextureCoordinates(Cube::Wall::Front, texture.getCoordinates(4, 16));

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

