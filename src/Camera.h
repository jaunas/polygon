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

using namespace glm;

class Camera {
public:
    Camera(vec3 position, vec3 front, vec3 up)
    : position(position), front(front), up(up)
    {
    }
    
    mat4 lookAt()
    {
        return glm::lookAt(position, position + front, up);
    }
    
    void goForward(float deltaTime)
    {
        position += speed * deltaTime * front;
    }
    
    void goBackwards(float deltaTime)
    {
        position -= speed * deltaTime * front;
    }
    
    void goLeft(float deltaTime)
    {
        position -= normalize(cross(front, up)) * speed * deltaTime;
    }
    
    void goRight(float deltaTime)
    {
        position += normalize(cross(front, up)) * speed * deltaTime;
    }
    
private:
    vec3 position;
    vec3 front;
    vec3 up;
    float speed = 2.5f;
};

#endif /* CAMERA_H */
