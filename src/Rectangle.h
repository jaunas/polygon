/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.h
 * Author: tomaszkowalewski
 *
 * Created on 9 sierpnia 2019, 13:07
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

class Rectangle {
public:
    Rectangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D)
    {
        transform = []() {
            return glm::mat4(1.0f);
        };
        
        vertices[Vertex::A] = A;
        vertices[Vertex::B] = B;
        vertices[Vertex::C] = C;
        vertices[Vertex::D] = D;
    }
    
    virtual ~Rectangle()
    {
    }
    
    void draw()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getTexture());

        vertexContainer.bind();

        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform()));

        // render the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void setShader(Shader shader)
    {
        this->shader = shader;
        this->shader.use();
        this->shader.setInt("tex", 0);
        transformLocation = glGetUniformLocation(this->shader.ID, "model");
    }
    
    void setTransformFunc(glm::mat4 (*transform)())
    {
        this->transform = transform;
    }
    
    void setTexture(Texture texture)
    {
        this->texture = texture;
    }
    
    void setTextureCoordinates(TextureCoordinates coordinates)
    {
        textureCoordinates = coordinates;
    }
    
    void loadVertices()
    {
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        prepareVertices();
        vertexContainer.
            loadVertices((float*)vertexAttributes, sizeof(vertexAttributes), indices, sizeof(indices));
    }
private:
    enum Vertex {A, B, C, D};
    glm::vec3 vertices[sizeof(Vertex)];
    TextureVertexContainer vertexContainer;
    Texture texture;
    Shader shader;
    unsigned int transformLocation;
    glm::mat4 (*transform)();
    TextureCoordinates textureCoordinates;
    float vertexAttributes[4][5];
    
    void prepareVertices()
    {
        glm::vec2 leftBottom = textureCoordinates.leftBottom;
        glm::vec2 rightTop = textureCoordinates.rightTop;
        
        setVertexAttributes(Vertex::A, leftBottom);
        setVertexAttributes(Vertex::B, glm::vec2(rightTop.x, leftBottom.y));
        setVertexAttributes(Vertex::C, rightTop);
        setVertexAttributes(Vertex::D, glm::vec2(leftBottom.x, rightTop.y));
    }
    
    void setVertexAttributes(Vertex vertex, glm::vec2 textureCoordinates)
    {
        vertexAttributes[vertex][0] = vertices[vertex].x;
        vertexAttributes[vertex][1] = vertices[vertex].y;
        vertexAttributes[vertex][2] = vertices[vertex].z;
        vertexAttributes[vertex][3] = textureCoordinates.x;
        vertexAttributes[vertex][4] = textureCoordinates.y;
    }
};

#endif /* RECTANGLE_H */

