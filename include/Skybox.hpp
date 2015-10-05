#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Shader.hpp"
#include "Camera.hpp"

#include <vector>

class Skybox {
private:
	GLuint loadCubemap(std::vector<const GLchar*> faces);

	std::vector<const GLchar*> _faces;
	GLuint	_cubemapTexture;
	GLuint	_skyboxVAO;
	GLuint	_skyboxVBO;
	Shader _skyboxShader;

public:
	Skybox();
	~Skybox();
	void	render(Camera &camera, glm::mat4 &projection);

};
