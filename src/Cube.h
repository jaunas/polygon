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

#include <glm/glm.hpp>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

using namespace glm;

class Cube {
public:
    Cube(vec3 A, vec3 B, vec3 C, vec3 D, vec3 E, vec3 F, vec3 G, vec3 H);
    virtual ~Cube();
    void draw();
    void setShader(Shader shader);
    void setTexture(Texture texture);
    void setTransformFunc(mat4 (*transform)());
private:
    TextureVertexContainer vertexContainer;
    Texture texture;
    Shader shader;
    unsigned int transformLocation;
    mat4 (*transform)();
};

#endif /* CUBE_H */

