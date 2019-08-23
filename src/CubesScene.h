/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CubesScene.h
 * Author: tomaszkowalewski
 *
 * Created on 9 sierpnia 2019, 13:07
 */

#ifndef CUBES_SCENE_H
#define CUBES_SCENE_H

#include <glm/glm.hpp>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"
#include "Cube.h"

using namespace glm;

class CubesScene : public Cube {
public:
    CubesScene(vec3 A, vec3 B, vec3 C, vec3 D, vec3 E, vec3 F, vec3 G, vec3 H);
    virtual ~CubesScene();
    void draw();
};

#endif /* CUBES_SCENE_H */

