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
    Cube(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, glm::vec3 E, glm::vec3 F, glm::vec3 G, glm::vec3 H, Texture texture)
    {
        transform = []() {
            return glm::mat4(1.0f);
        };

        unsigned int indices[] = {};

        this->texture = texture;
        
        glm::vec4 dirtGrass = texture.getCoordinates(4, 16);
        glm::vec4 grass = texture.getCoordinates(3, 7);
        glm::vec4 dirt = texture.getCoordinates(3, 16);
        // struct { T s, t, p, q; }

        float vertices[] = {
            // Back wall
            E.x, E.y, E.z,  dirtGrass.t, dirtGrass.q,
            F.x, F.y, F.z,  dirtGrass.s, dirtGrass.q,
            G.x, G.y, G.z,  dirtGrass.s, dirtGrass.p,
            G.x, G.y, G.z,  dirtGrass.s, dirtGrass.p,
            H.x, H.y, H.z,  dirtGrass.t, dirtGrass.p,
            E.x, E.y, E.z,  dirtGrass.t, dirtGrass.q,

            // Front wall
            A.x, A.y, A.z,  dirtGrass.s, dirtGrass.q,
            B.x, B.y, B.z,  dirtGrass.t, dirtGrass.q,
            C.x, C.y, C.z,  dirtGrass.t, dirtGrass.p,
            C.x, C.y, C.z,  dirtGrass.t, dirtGrass.p,
            D.x, D.y, D.z,  dirtGrass.s, dirtGrass.p,
            A.x, A.y, A.z,  dirtGrass.s, dirtGrass.q,

            // Left wall
            D.x, D.y, D.z,  dirtGrass.t, dirtGrass.p,
            H.x, H.y, H.z,  dirtGrass.s, dirtGrass.p,
            E.x, E.y, E.z,  dirtGrass.s, dirtGrass.q,
            E.x, E.y, E.z,  dirtGrass.s, dirtGrass.q,
            A.x, A.y, A.z,  dirtGrass.t, dirtGrass.q,
            D.x, D.y, D.z,  dirtGrass.t, dirtGrass.p,

            // Right wall
            C.x, C.y, C.z,  dirtGrass.s, dirtGrass.p,
            G.x, G.y, G.z,  dirtGrass.t, dirtGrass.p,
            F.x, F.y, F.z,  dirtGrass.t, dirtGrass.q,
            F.x, F.y, F.z,  dirtGrass.t, dirtGrass.q,
            B.x, B.y, B.z,  dirtGrass.s, dirtGrass.q,
            C.x, C.y, C.z,  dirtGrass.s, dirtGrass.p,

            // Bottom wall
            E.x, E.y, E.z,  dirt.s, dirt.p,
            F.x, F.y, F.z,  dirt.t, dirt.p,
            B.x, B.y, B.z,  dirt.t, dirt.q,
            B.x, B.y, B.z,  dirt.t, dirt.q,
            A.x, A.y, A.z,  dirt.s, dirt.q,
            E.x, E.y, E.z,  dirt.s, dirt.p,

            // Top wall
            H.x, H.y, H.z,  grass.s, grass.p,
            G.x, G.y, G.z,  grass.t, grass.p,
            C.x, C.y, C.z,  grass.t, grass.q,
            C.x, C.y, C.z,  grass.t, grass.q,
            D.x, D.y, D.z,  grass.s, grass.q,
            H.x, H.y, H.z,  grass.s, grass.p
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
