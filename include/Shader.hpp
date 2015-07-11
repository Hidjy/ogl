

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
    GLuint _program;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
};

#endif
