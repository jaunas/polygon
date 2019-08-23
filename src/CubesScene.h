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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"
#include "Cube.h"

using namespace glm;

class CubesScene : public Cube {
public:
    CubesScene(vec3 A, vec3 B, vec3 C, vec3 D, vec3 E, vec3 F, vec3 G, vec3 H)
    : Cube(A, B, C, D, E, F, G, H)
    {
    }
    
    virtual ~CubesScene()
    {
    }

    void draw()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getTexture());

        vertexContainer.bind();

        vec3 cubePositions[] = {
            vec3( 0.0f,  0.0f,  0.0f), 
            vec3( 2.0f,  5.0f, -15.0f), 
            vec3(-1.5f, -2.2f, -2.5f),  
            vec3(-3.8f, -2.0f, -12.3f),  
            vec3( 2.4f, -0.4f, -3.5f),  
            vec3(-1.7f,  3.0f, -7.5f),  
            vec3( 1.3f, -2.0f, -2.5f),  
            vec3( 1.5f,  2.0f, -2.5f), 
            vec3( 1.5f,  0.2f, -1.5f), 
            vec3(-1.3f,  1.0f, -1.5f)  
        };

        for(unsigned int i = 0; i < 10; i++)
        {
            mat4 model(1.0f);
            model = translate(model, cubePositions[i]);
            float angle = 20.0f * i; 
            model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
            this->shader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
};

#endif /* CUBES_SCENE_H */

