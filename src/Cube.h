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
#include <array>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

class Cube {
public:
    enum Wall {
        Back, Front, Left, Right, Bottom, Top
    };

    Cube(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, glm::vec3 E, glm::vec3 F, glm::vec3 G, glm::vec3 H, Texture texture)
    : A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H)
    {
        transform = []() {
            return glm::mat4(1.0f);
        };

        this->texture = texture;
        
        TextureCoordinates dirtGrass = texture.getCoordinates(4, 16);
        TextureCoordinates grass = texture.getCoordinates(3, 7);
        TextureCoordinates dirt = texture.getCoordinates(3, 16);

        float vertices[] = {
            // Back wall
            E.x, E.y, E.z,  dirtGrass.rightTop.x,    dirtGrass.leftBottom.y,
            F.x, F.y, F.z,  dirtGrass.leftBottom.x,  dirtGrass.leftBottom.y,
            G.x, G.y, G.z,  dirtGrass.leftBottom.x,  dirtGrass.rightTop.y,
            G.x, G.y, G.z,  dirtGrass.leftBottom.x,  dirtGrass.rightTop.y,
            H.x, H.y, H.z,  dirtGrass.rightTop.x,    dirtGrass.rightTop.y,
            E.x, E.y, E.z,  dirtGrass.rightTop.x,    dirtGrass.leftBottom.y,

            // Front wall
            A.x, A.y, A.z,  dirtGrass.leftBottom.x,  dirtGrass.leftBottom.y,
            B.x, B.y, B.z,  dirtGrass.rightTop.x,    dirtGrass.leftBottom.y,
            C.x, C.y, C.z,  dirtGrass.rightTop.x,    dirtGrass.rightTop.y,
            C.x, C.y, C.z,  dirtGrass.rightTop.x,    dirtGrass.rightTop.y,
            D.x, D.y, D.z,  dirtGrass.leftBottom.x,  dirtGrass.rightTop.y,
            A.x, A.y, A.z,  dirtGrass.leftBottom.x,  dirtGrass.leftBottom.y,

            // Left wall
            D.x, D.y, D.z,  dirtGrass.rightTop.x,    dirtGrass.rightTop.y,
            H.x, H.y, H.z,  dirtGrass.leftBottom.x,  dirtGrass.rightTop.y,
            E.x, E.y, E.z,  dirtGrass.leftBottom.x,  dirtGrass.leftBottom.y,
            E.x, E.y, E.z,  dirtGrass.leftBottom.x,  dirtGrass.leftBottom.y,
            A.x, A.y, A.z,  dirtGrass.rightTop.x,    dirtGrass.leftBottom.y,
            D.x, D.y, D.z,  dirtGrass.rightTop.x,    dirtGrass.rightTop.y,

            // Right wall
            C.x, C.y, C.z,  dirtGrass.leftBottom.x, dirtGrass.rightTop.y,
            G.x, G.y, G.z,  dirtGrass.rightTop.x,   dirtGrass.rightTop.y,
            F.x, F.y, F.z,  dirtGrass.rightTop.x,   dirtGrass.leftBottom.y,
            F.x, F.y, F.z,  dirtGrass.rightTop.x,   dirtGrass.leftBottom.y,
            B.x, B.y, B.z,  dirtGrass.leftBottom.x, dirtGrass.leftBottom.y,
            C.x, C.y, C.z,  dirtGrass.leftBottom.x, dirtGrass.rightTop.y,

            // Bottom wall
            E.x, E.y, E.z,  dirt.leftBottom.x,  dirt.leftBottom.y,
            F.x, F.y, F.z,  dirt.rightTop.x,    dirt.leftBottom.y,
            B.x, B.y, B.z,  dirt.rightTop.x,    dirt.rightTop.y,
            B.x, B.y, B.z,  dirt.rightTop.x,    dirt.rightTop.y,
            A.x, A.y, A.z,  dirt.leftBottom.x,  dirt.rightTop.y,
            E.x, E.y, E.z,  dirt.leftBottom.x,  dirt.leftBottom.y,

            // Top wall
            H.x, H.y, H.z,  grass.leftBottom.x,     grass.rightTop.y,
            G.x, G.y, G.z,  grass.rightTop.x,       grass.rightTop.y,
            C.x, C.y, C.z,  grass.rightTop.x,       grass.leftBottom.y,
            C.x, C.y, C.z,  grass.rightTop.x,       grass.leftBottom.y,
            D.x, D.y, D.z,  grass.leftBottom.x,     grass.leftBottom.y,
            H.x, H.y, H.z,  grass.leftBottom.x,     grass.rightTop.y
        };
        
        vertexContainer.
            loadVertices(vertices, sizeof(vertices), {}, 0);
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
    
    void setTransformFunc(glm::mat4 (*transform)())
    {
        this->transform = transform;
    }

    void setWallTextureCoordinates(Wall wall, TextureCoordinates coordinates)
    {
        wallTextureCoordinates[wall] = coordinates;
    }
    
    void loadVertices()
    {
//        prepareVertices();
//        
//        vertexContainer.
//            loadVertices((float*)vertices, sizeof(vertices), {}, 0);
    }
    
protected:
    Texture texture;
    TextureVertexContainer vertexContainer;
    Shader shader;
    unsigned int transformLocation;
private:
    glm::vec3 A, B, C, D, E, F, G, H;
    glm::mat4 (*transform)();
//    float vertices[sizeof(Wall)][6][5];
    TextureCoordinates wallTextureCoordinates[sizeof(Wall)];
    
    void prepareVertices()
    {
    }
};

#endif /* CUBE_H */
