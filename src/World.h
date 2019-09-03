#ifndef WORLD_H
#define WORLD_H

#include "CubesScene.h"

class World {
public:
    World(unsigned int width, unsigned int height)
    {
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
    }
    
    virtual ~World()
    {
    }
    
    void render(Camera camera)
    {
        view = camera.lookAt();

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        scene.draw();
    }
private:
    CubesScene scene;
    unsigned int viewLocation, projectionLocation;
    glm::mat4 view;
};

#endif /* WORLD_H */

