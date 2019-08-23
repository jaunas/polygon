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
#include "CubesScene.h"

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
    
    CubesScene containers(
            vec3(-0.5f, -0.5f,  0.5f),
            vec3( 0.5f, -0.5f,  0.5f),
            vec3( 0.5f,  0.5f,  0.5f),
            vec3(-0.5f,  0.5f,  0.5f),
            vec3(-0.5f, -0.5f, -0.5f),
            vec3( 0.5f, -0.5f, -0.5f),
            vec3( 0.5f,  0.5f, -0.5f),
            vec3(-0.5f,  0.5f, -0.5f)
    );
    
    containers.setShader(shader);
    containers.setTexture(Texture("Resources/img/container.jpg", GL_RGB));
    
    float ratio = (float)SCR_WIDTH/(float)SCR_HEIGHT;
    mat4 projection;
    mat4 startProjection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
    float rotation = 0.0f;
    
    mat4 view, startView(1.0f);
    vec3 position(0.0f, 0.0f, -3.0f);

    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        // input
        // -----
        window.processInput(&position, &rotation);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projection = rotate(startProjection, radians(rotation), vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

        view = translate(startView, position);
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));
        
        containers.draw();

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
    return rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
}