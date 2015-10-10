#include "RenderContext.hpp"

#include "ShaderManager.hpp"

RenderContext::RenderContext() {
	_shaderManager = new ShaderManager();
}

RenderContext::~RenderContext() {
	delete _shaderManager;
}

ShaderManager *RenderContext::getShaderManager() {
	return _shaderManager;
}

glm::mat4		RenderContext::getProjectionMatrix() {
	return _projectionMatrix;
}

glm::mat4		RenderContext::getViewMatrix() {
	return _viewMatrix;
}

void			RenderContext::setProjectionMatrix(glm::mat4 newMatrix) {
	_projectionMatrix = newMatrix;
}

void			RenderContext::setViewMatrix(glm::mat4 newMatrix) {
	_viewMatrix = newMatrix;
}
