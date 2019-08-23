/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: tomaszkowalewski
 *
 * Created on 19 lipca 2019, 14:58
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Window {
public:
    Window(const unsigned int width, const unsigned int height)
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
            {
                // make sure the viewport matches the new window dimensions; note that width and
                // height will be significantly larger than specified on retina displays.
                glViewport(0, 0, width, height);
            }
        );

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }
    }
    
    virtual ~Window()
    {
        glfwTerminate();
    }
    
    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }
    
    void processInput(glm::vec3* position, float* rotation)
    {
        float dp = 0.02f;
        float dr = 1.f;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            position->x -= dp*(glm::sin(glm::radians(*rotation)));
            position->z += dp*(glm::cos(glm::radians(*rotation)));
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            position->x += dp*(glm::sin(glm::radians(*rotation)));
            position->z -= dp*(glm::cos(glm::radians(*rotation)));
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            *rotation += dr;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            *rotation -= dr;
        }
    }
    
    void swapBuffers()
    {
        glfwSwapBuffers(window);
    }
private:
    GLFWwindow* window;
};

#endif /* WINDOW_H */

