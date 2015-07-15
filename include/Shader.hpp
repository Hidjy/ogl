

#ifndef SHADER_HPP
#define SHADER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.hpp"


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
