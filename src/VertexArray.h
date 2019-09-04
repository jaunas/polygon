#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

class VertexArray {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords;
    };
    
    VertexArray()
    {
    }
    
    virtual ~VertexArray()
    {
    }
    
    void addVertex(Vertex vertex)
    {
        m_attributes.push_back(vertex);
    }
    
    void addVertex(glm::vec3 position, glm::vec2 texCoords)
    {
        Vertex vertex;
        vertex.position = position;
        vertex.texCoords = texCoords;
        
        addVertex(vertex);
    }
    
    void loadVertices()
    {
        float vertices[m_attributes.size() * sizeof(float) * 5];

        int i=0;
        for (Vertex vertex : m_attributes) {
            vertices[(i*5)+0] = vertex.position.x;
            vertices[(i*5)+1] = vertex.position.y;
            vertices[(i*5)+2] = vertex.position.z;
            
            vertices[(i*5)+3] = vertex.texCoords.x;
            vertices[(i*5)+4] = vertex.texCoords.y;
            i++;
        }
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(0);

        this->setAttributes();

        // Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
    }
    
    void bind()
    {
        glBindVertexArray(VAO);
    }
protected:
    virtual void setAttributes()
    {
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
    }
private:
    unsigned int VBO, VAO;
    std::vector<Vertex> m_attributes;
};

#endif /* VERTEX_ARRAY_H */

