#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

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
};

#endif
