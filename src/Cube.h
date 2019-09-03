#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>
#include <array>
#include <iostream>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

class Cube {
public:
    enum Wall {
        Back, Front, Left, Right, Bottom, Top
    };

    Cube(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, glm::vec3 E, glm::vec3 F, glm::vec3 G, glm::vec3 H)
    {
        transform = []() {
            return glm::mat4(1.0f);
        };

        vertices[Vertex::A] = A;
        vertices[Vertex::B] = B;
        vertices[Vertex::C] = C;
        vertices[Vertex::D] = D;
        vertices[Vertex::E] = E;
        vertices[Vertex::F] = F;
        vertices[Vertex::G] = G;
        vertices[Vertex::H] = H;
    }
    
    virtual ~Cube() {}
    
    void draw()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getTexture());

        vertexContainer.bind();

        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform()));

        // render the triangle
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    void setShader(Shader shader)
    {
        this->shader = shader;
        this->shader.use();
        this->shader.setInt("tex", 0);
        transformLocation = glGetUniformLocation(this->shader.ID, "model");
    }
    
    void setTexture(Texture texture)
    {
        this->texture = texture;
    }
    
    void setTransformFunc(glm::mat4 (*transform)())
    {
        this->transform = transform;
    }

    void setTextureCoordinates(Wall wall, TextureCoordinates coordinates)
    {
        textureCoordinates[wall] = coordinates;
    }
    
    void loadVertices()
    {
        prepareVertices();
        
        vertexContainer.
            loadVertices((float*)vertexAttributes, sizeof(vertexAttributes), {}, 0);
    }
    
protected:
    Texture texture;
    TextureVertexContainer vertexContainer;
    Shader shader;
    unsigned int transformLocation;
private:
    enum Vertex {A, B, C, D, E, F, G, H};
    glm::vec3 vertices[8];
    glm::mat4 (*transform)();
    float vertexAttributes[6][6][5];
    TextureCoordinates textureCoordinates[6];
    
    void prepareVertices()
    {
        setWallAttributes(Wall::Back, Vertex::F, Vertex::E, Vertex::H, Vertex::G);
        setWallAttributes(Wall::Front, Vertex::A, Vertex::B, Vertex::C, Vertex::D);
        setWallAttributes(Wall::Left, Vertex::E, Vertex::A, Vertex::D, Vertex::H);
        setWallAttributes(Wall::Right, Vertex::B, Vertex::F, Vertex::G, Vertex::C);
        setWallAttributes(Wall::Bottom, Vertex::E, Vertex::F, Vertex::B, Vertex::A);
        setWallAttributes(Wall::Top, Vertex::D, Vertex::C, Vertex::G, Vertex::H);
    }
    
    void setWallAttributes(Wall wall, Vertex A, Vertex B, Vertex C, Vertex D)
    {
        TextureCoordinates coordinates = textureCoordinates[wall];
        
        glm::vec2 rightLeft(coordinates.rightTop.x, coordinates.leftBottom.y);
        glm::vec2 leftRight(coordinates.leftBottom.x, coordinates.rightTop.y);
        
        setVertexAttributes(wall, 0, A, coordinates.leftBottom);
        setVertexAttributes(wall, 1, B, rightLeft);
        setVertexAttributes(wall, 2, C, coordinates.rightTop);
        setVertexAttributes(wall, 3, C, coordinates.rightTop);
        setVertexAttributes(wall, 4, D, leftRight);
        setVertexAttributes(wall, 5, A, coordinates.leftBottom);
    }
    
    void setVertexAttributes(Wall wall, unsigned int triangle, Vertex vertex, glm::vec2 textureCoordinates)
    {
        vertexAttributes[wall][triangle][0] = vertices[vertex].x;
        vertexAttributes[wall][triangle][1] = vertices[vertex].y;
        vertexAttributes[wall][triangle][2] = vertices[vertex].z;
        vertexAttributes[wall][triangle][3] = textureCoordinates.x;
        vertexAttributes[wall][triangle][4] = textureCoordinates.y;
    }
};

#endif /* CUBE_H */
