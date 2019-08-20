#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include "Window.h"
#include "Texture.h"
#include "Rectangle.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace glm;

mat4 transform1();
mat4 transform2();

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);
    
    Shader shader("src/shader/shader.vs", "src/shader/shader.fs");
    
    Rectangle container = Rectangle(
            vec3( 0.5f,  0.5f, 0.0f),
            vec3( 0.5f, -0.5f, 0.0f),
            vec3(-0.5f, -0.5f, 0.0f),
            vec3(-0.5f,  0.5f, 0.0f)
    );
    
    container.setShader(shader);
    container.setTexture(Texture("Resources/img/container.jpg", GL_RGB));
    container.setTransformFunc(transform1);
    
    Rectangle smile = Rectangle(
            vec3( 0.5f,  0.5f, 0.0f),
            vec3( 0.5f, -0.5f, 0.0f),
            vec3(-0.5f, -0.5f, 0.0f),
            vec3(-0.5f,  0.5f, 0.0f)
    );
    
    smile.setShader(shader);
    smile.setTexture(Texture("Resources/img/awesomeface.png", GL_RGBA));
    smile.setTransformFunc(transform2);
    
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        // input
        // -----
        window.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        container.draw();
        smile.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}

mat4 transform1()
{
    mat4 trans = mat4(1.0f);
    
    float time = glfwGetTime();
    float scale = std::sin(time) * std::sin(time);
    
    return glm::scale(trans, glm::vec3(scale, scale, 1.0f));
}

mat4 transform2()
{
    mat4 trans = mat4(1.0f);
    
    float time = glfwGetTime();
    float pos = std::sin(time);
    
    return glm::translate(trans, glm::vec3(pos, 0.0f, 0.0f));
}