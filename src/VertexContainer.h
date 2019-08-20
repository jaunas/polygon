/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VertexContainer.h
 * Author: tomaszkowalewski
 *
 * Created on 19 lipca 2019, 14:24
 */

#ifndef VERTEX_CONTAINER_H
#define VERTEX_CONTAINER_H

class VertexContainer {
public:
    VertexContainer();
    virtual ~VertexContainer();
    void loadVertices(float vertices[], int verticesNum, unsigned int indices[], unsigned int indicesNum);
    void bind();
private:
    unsigned int VBO, VAO, EBO;
};

#endif /* VERTEX_CONTAINER_H */

