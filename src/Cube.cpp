/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cube.cpp
 * Author: tomaszkowalewski
 * 
 * Created on 9 sierpnia 2019, 13:07
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include <iostream>

#include "Cube.h"
#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

using namespace glm;

mat4 t1();

Cube::Cube(vec3 A, vec3 B, vec3 C, vec3 D, vec3 E, vec3 F, vec3 G, vec3 H)
{
    transform = t1;
    
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

Cube::~Cube()
{
}

void Cube::draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTexture());
    
    vertexContainer.bind();
    
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform()));
    
    // render the triangle
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::setTransformFunc(mat4 (*transform)())
{
    this->transform = transform;
}

void Cube::setTexture(Texture texture)
{
    this->texture = texture;
}

void Cube::setShader(Shader shader)
{
    this->shader = shader;
    this->shader.use();
    this->shader.setInt("tex", 0);
    transformLocation = glGetUniformLocation(this->shader.ID, "model");
}

mat4 t1()
{
    return mat4(1.0f);
}