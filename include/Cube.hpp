#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Cube{
public:
	glm::vec3	pos;
	//Texture	faces[6];
	GLuint		faces[6];

	Cube(glm::vec3 pos, GLuint faces[6]);
};
