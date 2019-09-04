#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <SFML/System/Vector2.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include "TextureVertexContainer.h"

class Camera {
public:
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    Camera()
    : m_position(glm::vec3(0.0f, 0.0f, 3.0f)), m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f))
    {
    }
    
    glm::mat4 lookAt()
    {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }
    
    void go(Direction direction, float deltaTime)
    {
        float step = m_speed * deltaTime;
        float y = m_position.y;
        
        switch (direction) {
            case FORWARD:
                m_position += step * m_front;
                break;
            case BACKWARD:
                m_position -= step * m_front;
                break;
            case LEFT:
                m_position -= glm::normalize(glm::cross(m_front, m_up)) * step;
                break;
            case RIGHT:
                m_position += glm::normalize(glm::cross(m_front, m_up)) * step;
                break;
        }
        
        m_position.y = y;
    }
    
    void processMouseMovement(sf::Vector2i pos)
    {
        if (m_firstMouse) {
            m_lastX = pos.x;
            m_lastY = pos.y;
            m_firstMouse = false;
        }

        float xoffset = pos.x - m_lastX;
        float yoffset = m_lastY - pos.y;
        m_lastX = pos.x;
        m_lastY = pos.y;

        xoffset *= m_sensitivity;
        yoffset *= m_sensitivity;

        m_yaw = glm::mod((m_yaw + xoffset), (GLfloat)360.0f);
        m_pitch += yoffset;

        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }

        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
        
        m_front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
        m_front.y = sin(glm::radians(m_pitch));
        m_front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
        
        m_front = glm::normalize(m_front);
    }
    
private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    
    float m_speed = 2.5f;
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_sensitivity = 0.05f;
    float m_lastX, m_lastY;
    bool m_firstMouse = true;
};

#endif /* CAMERA_H */
