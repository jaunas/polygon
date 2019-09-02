#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "Texture.h"
#include "CubesScene.h"
#include "Camera.h"
#include "Rectangle.h"
#include "Application.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Application app(
        SCR_WIDTH, SCR_HEIGHT,
        Camera(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            SCR_WIDTH,
            SCR_HEIGHT
        ),
        CubesScene(
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3( 0.5f, -0.5f,  0.5f),
            glm::vec3( 0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3( 0.5f, -0.5f, -0.5f),
            glm::vec3( 0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f)
        )
    );
    
    app.runLoop();
    
    return 0;
}
