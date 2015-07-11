

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
private:
    GLuint _program;

public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    GLuint getProgram();
    void Use();
};

#endif
