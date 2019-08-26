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

    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
    : position(position), front(front), up(up)
    {
    }
    
    glm::mat4 lookAt()
    {
        return glm::lookAt(position, position + front, up);
    }
    
    void go(Direction direction, float deltaTime)
    {
        float step = speed * deltaTime;
        
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
    }
    
    void update(float pitch, float yaw)
    {
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
};

#endif /* CAMERA_H */
