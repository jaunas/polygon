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

class Window {
public:
            Window(const unsigned int width, const unsigned int height);
    virtual ~Window();
    bool    shouldClose();
    void    processInput(glm::vec3* position, float* rotation);
    void    swapBuffers();
private:
    GLFWwindow* window;
};

#endif /* WINDOW_H */

