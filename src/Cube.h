#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>
#include <array>
#include <iostream>

#include "VertexArray.h"

class Cube {
public:
    enum Wall {
        Back, Front, Left, Right, Bottom, Top
    };
    
    struct TextureCoordinates {
        glm::vec2 leftBottom;
        glm::vec2 rightTop;
    };

    Cube(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, glm::vec3 E, glm::vec3 F, glm::vec3 G, glm::vec3 H)
    {
        m_transform = []() {
            return glm::mat4(1.0f);
        };

        m_vertices[Vertex::A] = A;
        m_vertices[Vertex::B] = B;
        m_vertices[Vertex::C] = C;
        m_vertices[Vertex::D] = D;
        m_vertices[Vertex::E] = E;
        m_vertices[Vertex::F] = F;
        m_vertices[Vertex::G] = G;
        m_vertices[Vertex::H] = H;
    }
    
    virtual ~Cube() {}
    
    void draw()
    {
        sf::Texture::bind(&m_texture);

        m_vertexArray.bind();

        m_shader->setUniform("model", sf::Glsl::Mat4(glm::value_ptr(m_transform())));

        // render the triangle
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    void setShader(sf::Shader* shader)
    {
        m_shader = shader;
        sf::Shader::bind(m_shader);
        m_shader->setUniform("tex", m_texture);
    }
    
    void setTexture(sf::Texture texture)
    {
        m_texture = texture;
    }
    
    void setTransformFunc(glm::mat4 (*transform)())
    {
        m_transform = transform;
    }

    void setTextureCoordinates(Wall wall, sf::IntRect intRect)
    {
        TextureCoordinates coordinates;
        coordinates.leftBottom = glm::vec2(
            (float)intRect.left/m_texture.getSize().x,
            (float)(intRect.top+intRect.height)/m_texture.getSize().y
        );
        coordinates.rightTop = glm::vec2(
            (float)(intRect.left+intRect.width)/m_texture.getSize().x,
            (float)intRect.top/m_texture.getSize().y
        );
        
        m_textureCoordinates[wall] = coordinates;
    }

    void loadVertices()
    {
        prepareVertices();
        m_vertexArray.loadVertices();
    }
    
protected:
    sf::Texture m_texture;
    VertexArray m_vertexArray;
    sf::Shader* m_shader;
private:
    enum Vertex {A, B, C, D, E, F, G, H};
    glm::vec3 m_vertices[8];
    glm::mat4 (*m_transform)();
    TextureCoordinates m_textureCoordinates[6];
    
    void prepareVertices()
    {
        setWallAttributes(Wall::Back, Vertex::F, Vertex::E, Vertex::H, Vertex::G);
        setWallAttributes(Wall::Front, Vertex::A, Vertex::B, Vertex::C, Vertex::D);
        setWallAttributes(Wall::Left, Vertex::E, Vertex::A, Vertex::D, Vertex::H);
        setWallAttributes(Wall::Right, Vertex::B, Vertex::F, Vertex::G, Vertex::C);
        setWallAttributes(Wall::Bottom, Vertex::E, Vertex::F, Vertex::B, Vertex::A);
        setWallAttributes(Wall::Top, Vertex::D, Vertex::C, Vertex::G, Vertex::H);
    }
    
    void setWallAttributes(Wall wall, Vertex A, Vertex B, Vertex C, Vertex D)
    {
        TextureCoordinates coordinates = m_textureCoordinates[wall];
        
        glm::vec2 rightBottom(coordinates.rightTop.x, coordinates.leftBottom.y);
        glm::vec2 leftTop(coordinates.leftBottom.x, coordinates.rightTop.y);
        
        m_vertexArray.addVertex(m_vertices[A], coordinates.leftBottom);
        m_vertexArray.addVertex(m_vertices[B], rightBottom);
        m_vertexArray.addVertex(m_vertices[C], coordinates.rightTop);
        m_vertexArray.addVertex(m_vertices[C], coordinates.rightTop);
        m_vertexArray.addVertex(m_vertices[D], leftTop);
        m_vertexArray.addVertex(m_vertices[A], coordinates.leftBottom);
    }
};

#endif /* CUBE_H */
