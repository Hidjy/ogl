#pragma once

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
