#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "IRenderContext.hpp"

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
	void	render(IRenderContext *renderContext);

};
