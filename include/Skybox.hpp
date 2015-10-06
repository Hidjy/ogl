#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer.hpp"
#include "Shader.hpp"

#include <vector>

class Skybox {
private:
	GLuint loadCubemap(std::vector<const GLchar*> faces);

	std::vector<const GLchar*> _faces;
	GLuint	_cubemapTexture;
	GLuint	_skyboxVAO;
	GLuint	_skyboxVBO;

public:
	Skybox();
	~Skybox();
	void	render(Renderer *renderer);

};
