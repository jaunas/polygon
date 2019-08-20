/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureVertexContainer.cpp
 * Author: tomaszkowalewski
 * 
 * Created on 19 lipca 2019, 14:24
 */

#include "TextureVertexContainer.h"

#include <glad/glad.h>

TextureVertexContainer::TextureVertexContainer()
{
}


TextureVertexContainer::~TextureVertexContainer()
{
}

void TextureVertexContainer::setAttributes()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
}