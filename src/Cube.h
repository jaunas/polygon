/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cube.h
 * Author: tomaszkowalewski
 *
 * Created on 9 sierpnia 2019, 13:07
 */

#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

class Cube {
public:
    Cube(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, glm::vec3 E, glm::vec3 F, glm::vec3 G, glm::vec3 H)
    {
        transform = []() {
            return glm::mat4(1.0f);
        };

        unsigned int indices[] = {};

        float vertices[] = {
            // Back wall
            E.x, E.y, E.z,  0.0f, 0.0f,
            F.x, F.y, F.z,  1.0f, 0.0f,
            G.x, G.y, G.z,  1.0f, 1.0f,
            G.x, G.y, G.z,  1.0f, 1.0f,
            H.x, H.y, H.z,  0.0f, 1.0f,
            E.x, E.y, E.z,  0.0f, 0.0f,

            // Front wall
            A.x, A.y, A.z,  0.0f, 0.0f,
            B.x, B.y, B.z,  1.0f, 0.0f,
            C.x, C.y, C.z,  1.0f, 1.0f,
            C.x, C.y, C.z,  1.0f, 1.0f,
            D.x, D.y, D.z,  0.0f, 1.0f,
            A.x, A.y, A.z,  0.0f, 0.0f,

            // Left wall
            D.x, D.y, D.z,  1.0f, 0.0f,
            H.x, H.y, H.z,  1.0f, 1.0f,
            E.x, E.y, E.z,  0.0f, 1.0f,
            E.x, E.y, E.z,  0.0f, 1.0f,
            A.x, A.y, A.z,  0.0f, 0.0f,
            D.x, D.y, D.z,  1.0f, 0.0f,

            // Right wall
            C.x, C.y, C.z,  1.0f, 0.0f,
            G.x, G.y, G.z,  1.0f, 1.0f,
            F.x, F.y, F.z,  0.0f, 1.0f,
            F.x, F.y, F.z,  0.0f, 1.0f,
            B.x, B.y, B.z,  0.0f, 0.0f,
            C.x, C.y, C.z,  1.0f, 0.0f,

            // Bottom wall
            E.x, E.y, E.z,  0.0f, 1.0f,
            F.x, F.y, F.z,  1.0f, 1.0f,
            B.x, B.y, B.z,  1.0f, 0.0f,
            B.x, B.y, B.z,  1.0f, 0.0f,
            A.x, A.y, A.z,  0.0f, 0.0f,
            E.x, E.y, E.z,  0.0f, 1.0f,

            // Top wall
            H.x, H.y, H.z,  0.0f, 1.0f,
            G.x, G.y, G.z,  1.0f, 1.0f,
            C.x, C.y, C.z,  1.0f, 0.0f,
            C.x, C.y, C.z,  1.0f, 0.0f,
            D.x, D.y, D.z,  0.0f, 0.0f,
            H.x, H.y, H.z,  0.0f, 1.0f
        };

        vertexContainer.
            loadVertices(vertices, sizeof(vertices), indices, sizeof(indices));
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

protected:
    Texture texture;
    TextureVertexContainer vertexContainer;
    Shader shader;
    unsigned int transformLocation;
private:
    glm::mat4 (*transform)();
};

#endif /* CUBE_H */
