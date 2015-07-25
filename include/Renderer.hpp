#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "TextureManager.hpp"

class Renderer {
private:
	Shader		*_blockShader;
	Shader		*_skyboxShader;
	Shader		*_textShader;

	TextureManager *_textureManager;

public:
	Renderer();
	~Renderer();

	Shader *getBlockShader();
	Shader *getSkyboxShader();
	Shader *getTextShader();

	TextureManager *getTextureManager();


	void	setBlockShader(Shader *shader);
	void	setSkyboxShader(Shader *shader);
	void	setTextShader(Shader *shader);

	void	setTextureManager(TextureManager *TextureManager);

};
