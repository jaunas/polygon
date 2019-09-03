#ifndef TEXTURE_VERTEX_CONTAINER_H
#define TEXTURE_VERTEX_CONTAINER_H

#include <glad/glad.h>

#include "VertexContainer.h"

class TextureVertexContainer : public VertexContainer {
public:
    TextureVertexContainer()
    {
    }
    
    virtual ~TextureVertexContainer()
    {
    }
    
protected:
    void setAttributes()
    {
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
    }
};

#endif /* TEXTURE_VERTEX_CONTAINER_H */

