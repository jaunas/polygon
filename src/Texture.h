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

#include "external/stb_image.h"

#include <glad/glad.h>

#include <iostream>
#include <string>

using namespace std;

class Texture {
public:
    Texture()
    {
        
    }
    
    Texture(const string &path, GLenum format)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            cout << "Failed to load texture" << endl;
            exit(-1);
        }

        stbi_image_free(data);
    }
    
    virtual ~Texture()
    {
    }
    
    unsigned int getTexture() const
    {
        return texture;
    }

private:
    unsigned int texture;
};

#endif /* TEXTURE_H */

