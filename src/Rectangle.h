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

        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        float vertices[] = {
            A.x, A.y, A.z, 1.0f, 1.0f,
            B.x, B.y, B.z, 1.0f, 0.0f,
            C.x, C.y, C.z, 0.0f, 0.0f,
            D.x, D.y, D.z, 0.0f, 1.0f
        };

        vertexContainer.
            loadVertices(vertices, sizeof(vertices), indices, sizeof(indices));
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
    
    void setTexture(Texture texture)
    {
        this->texture = texture;
    }
    
    void setTransformFunc(glm::mat4 (*transform)())
    {
        this->transform = transform;
    }
private:
    TextureVertexContainer vertexContainer;
    Texture texture;
    Shader shader;
    unsigned int transformLocation;
    glm::mat4 (*transform)();
};

#endif /* RECTANGLE_H */

