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
#include "Cube.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace glm;

mat4 trans1();

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);
    
    unsigned int viewLocation, projectionLocation;
    
    Shader shader("src/shader/textureShader.vs", "src/shader/textureShader.fs");
    
    viewLocation = glGetUniformLocation(shader.ID, "view");
    projectionLocation = glGetUniformLocation(shader.ID, "projection");    
    
    Cube container = Cube(
            vec3( 0.5f,  0.5f, 0.0f),
            vec3( 0.5f, -0.5f, 0.0f),
            vec3(-0.5f, -0.5f, 0.0f),
            vec3(-0.5f,  0.5f, 0.0f)
    );
    
    container.setShader(shader);
    container.setTexture(Texture("Resources/img/container.jpg", GL_RGB));
    container.setTransformFunc(trans1);
    
    mat4 view(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -3.0f));
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

    float ratio = (float)SCR_WIDTH/(float)SCR_HEIGHT;
    mat4 projection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

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

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}

mat4 trans1()
{
    mat4 model(1.0f);
    return rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
}