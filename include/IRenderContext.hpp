#pragma once

#include "ShaderManager.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IRenderContext {
public:
	virtual ~IRenderContext() {};

	virtual ShaderManager *getShaderManager() = 0;

	virtual glm::mat4		getProjectionMatrix() = 0;
	virtual glm::mat4		getViewMatrix() = 0;

	virtual void			setProjectionMatrix(glm::mat4 newMatrix) = 0;
	virtual void			setViewMatrix(glm::mat4 newMatrix) = 0;
};
