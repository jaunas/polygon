/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Texture.h
 * Author: tomaszkowalewski
 *
 * Created on 23 lipca 2019, 12:18
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string>

using namespace std;

class Texture {
public:
    Texture();
    Texture(const string &path, GLenum format);
    virtual ~Texture();
    unsigned int getTexture() const;
private:
    unsigned int texture;
};

#endif /* TEXTURE_H */

