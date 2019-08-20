/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureVertexContainer.h
 * Author: tomaszkowalewski
 *
 * Created on 19 lipca 2019, 14:24
 */

#ifndef TEXTURE_VERTEX_CONTAINER_H
#define TEXTURE_VERTEX_CONTAINER_H

#include "VertexContainer.h"

class TextureVertexContainer : public VertexContainer {
public:
    TextureVertexContainer();
    virtual ~TextureVertexContainer();
protected:
    void setAttributes();
};

#endif /* TEXTURE_VERTEX_CONTAINER_H */

