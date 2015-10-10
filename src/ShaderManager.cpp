#include "ShaderManager.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>

#include "Shader.hpp"

ShaderManager::ShaderManager() {
	_shaders.clear();
}

ShaderManager::~ShaderManager() {
	for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
	{
		delete it->second;
	}
}

Shader *ShaderManager::getShader(std::string name) {
	auto it = _shaders.find(name);
	if (it != _shaders.end())
		return it->second;
	return nullptr;
}


void	ShaderManager::setShader(std::string name, Shader *shader) {
	_shaders[name] = shader;
}
