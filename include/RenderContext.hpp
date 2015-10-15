#pragma once

#include "IRenderContext.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.hpp"
#include "RenderContext.hpp"

class RenderContext : public IRenderContext {
private:
	ShaderManager *_shaderManager;

	glm::mat4		_projectionMatrix;
	glm::mat4		_viewMatrix;

public:
	RenderContext();
	~RenderContext();

	ShaderManager *getShaderManager();

	glm::mat4		getProjectionMatrix();
	glm::mat4		getViewMatrix();

	void			setProjectionMatrix(glm::mat4 newMatrix);
	void			setViewMatrix(glm::mat4 newMatrix);
};
