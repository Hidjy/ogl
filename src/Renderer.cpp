#include "Renderer.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "TextureManager.hpp"

Renderer::Renderer() {
	_blockShader = nullptr;
	_skyboxShader = nullptr;
	_textShader = nullptr;
	_textureManager = nullptr;
}

Renderer::~Renderer() {
	if (_blockShader != nullptr)
		delete _blockShader;
	if (_skyboxShader != nullptr)
		delete _skyboxShader;
	if (_textShader != nullptr)
		delete _textShader;
	if (_textureManager != nullptr)
		delete _textureManager;
}

Shader *Renderer::getBlockShader() {
	return _blockShader;
}

Shader *Renderer::getSkyboxShader() {
	return _skyboxShader;
}

Shader *Renderer::getTextShader() {
	return _textShader;
}

TextureManager *Renderer::getTextureManager() {
	return _textureManager;
}

void	Renderer::setBlockShader(Shader *shader) {
	_blockShader = shader;
}

void	Renderer::setSkyboxShader(Shader *shader) {
	_skyboxShader = shader;
}

void	Renderer::setTextShader(Shader *shader) {
	_textShader = shader;
}

void	Renderer::setTextureManager(TextureManager *tm) {
	_textureManager = tm;
}
