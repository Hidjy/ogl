#include "Cube.hpp"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

Cube::Cube(glm::vec3 p, GLuint f[6]) : pos(p) {
	for (size_t i = 0; i < 6; i++) {
		this->faces[i] = f[i];
	}
}
