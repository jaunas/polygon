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

#include <glad/glad.h>

class VertexContainer {
public:
    VertexContainer()
    {
    }
    
    virtual ~VertexContainer()
    {
    }
    
    void loadVertices(float vertices[], int verticesNum, unsigned int indices[], unsigned int indicesNum)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesNum, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesNum, indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(0);

        this->setAttributes();

        // Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0);
    }
    
    void bind()
    {
        glBindVertexArray(VAO);
    }
protected:
    virtual void setAttributes()
    {
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(0);
    }
private:
    unsigned int VBO, VAO, EBO;
};

#endif /* VERTEX_CONTAINER_H */

