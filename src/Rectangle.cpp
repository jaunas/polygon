/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.cpp
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

#include "Rectangle.h"
#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

using namespace glm;

mat4 t();

Rectangle::Rectangle(vec3 A, vec3 B, vec3 C, vec3 D)
{
    transform = t;
    
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

Rectangle::~Rectangle()
{
}

void Rectangle::draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTexture());
    
    vertexContainer.bind();
    
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform()));
    
    // render the triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::setTransformFunc(mat4 (*transform)())
{
    this->transform = transform;
}

void Rectangle::setTexture(Texture texture)
{
    this->texture = texture;
}

void Rectangle::setShader(Shader shader)
{
    this->shader = shader;
    this->shader.use();
    this->shader.setInt("tex", 0);
    transformLocation = glGetUniformLocation(this->shader.ID, "model");
}

mat4 t()
{
    return mat4(1.0f);
}