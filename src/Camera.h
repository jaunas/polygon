#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include "TextureVertexContainer.h"
#include "Texture.h"
#include "Shader.h"

class Camera {
public:
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    Camera(
        glm::vec3 position,
        glm::vec3 front,
        glm::vec3 up,
        const unsigned int width,
        const unsigned int height
    ) : position(position), front(front), up(up)
    {
    }
    
    glm::mat4 lookAt()
    {
        return glm::lookAt(position, position + front, up);
    }
    
    void go(Direction direction, float deltaTime)
    {
        float step = speed * deltaTime;
        float y = position.y;
        
        switch (direction) {
            case FORWARD:
                position += step * front;
                break;
            case BACKWARD:
                position -= step * front;
                break;
            case LEFT:
                position -= glm::normalize(glm::cross(front, up)) * step;
                break;
            case RIGHT:
                position += glm::normalize(glm::cross(front, up)) * step;
                break;
        }
        
        position.y = y;
    }
    
    void processMouseMovement(double xpos, double ypos)
    {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw = glm::mod((yaw + xoffset), (GLfloat)360.0f);
        pitch += yoffset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }

        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
        
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        
        front = glm::normalize(front);
    }
    
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    
    float speed = 2.5f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float sensitivity = 0.05f;
    float lastX, lastY;
    bool firstMouse = true;
};

#endif /* CAMERA_H */
