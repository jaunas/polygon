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

#include <glm/glm.hpp>

#include "VertexContainer.h"
#include "Texture.h"
#include "Shader.h"

using namespace glm;

class Rectangle {
public:
    Rectangle(vec3 A, vec3 B, vec3 C, vec3 D);
    virtual ~Rectangle();
    void draw();
    void setShader(Shader shader);
    void setTexture(Texture texture);
    void setTransformFunc(mat4 (*transform)());
private:
    VertexContainer vertexContainer;
    Texture texture;
    Shader shader;
    unsigned int transformLocation;
    mat4 (*transform)();
};

#endif /* RECTANGLE_H */

