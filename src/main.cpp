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
#include "Camera.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Camera camera(
    glm::vec3(0.0f, 0.0f, 3.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
);

float lastX = ((float)SCR_WIDTH)/2.0f;
float lastY = ((float)SCR_HEIGHT)/2.0f;

float yaw = -90.0f;
float pitch = 0.0f;

bool firstMouse = true;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);
    window.enableMouseCallback(mouse_callback);
    
    unsigned int viewLocation, projectionLocation;
    
    Shader shader("src/shader/textureShader.vs", "src/shader/textureShader.fs");
    
    viewLocation = glGetUniformLocation(shader.ID, "view");
    projectionLocation = glGetUniformLocation(shader.ID, "projection");    
    
    CubesScene containers(
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3( 0.5f, -0.5f,  0.5f),
            glm::vec3( 0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3( 0.5f, -0.5f, -0.5f),
            glm::vec3( 0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f)
    );
    
    containers.setShader(shader);
    containers.setTexture(Texture("Resources/img/container.jpg", GL_RGB));
    
    float ratio = (float)SCR_WIDTH/(float)SCR_HEIGHT;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
    
    glm::mat4 view;

    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        // input
        // -----
        window.processInput(&camera);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = camera.lookAt();

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        
        containers.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;
    
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    
    camera.update(pitch, yaw);
}
