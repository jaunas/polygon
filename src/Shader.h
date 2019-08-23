#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>

#include <string>

using namespace std;

class Shader
{
public:
    // the program ID
    unsigned int ID;

    Shader();
    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    void setMat4(const string &name, const glm::mat4 &mat) const;
};

#endif
