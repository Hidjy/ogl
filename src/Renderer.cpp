#include "Renderer.hpp"

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

Renderer::Renderer() {
	_shaders.clear();
}

Renderer::~Renderer() {
	for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
	{
		delete it->second;
	}
}

Shader *Renderer::getShader(std::string name) {
	auto it = _shaders.find(name);
	if (it != _shaders.end())
		return it->second;
	return nullptr;
}


void	Renderer::setShader(std::string name, Shader *shader) {
	_shaders[name] = shader;
}
