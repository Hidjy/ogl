#pragma once

#include <map>
#include <string>

#include "Shader.hpp"

class Renderer {
private:
	std::map<std::string, Shader *>	_shaders;

public:
	Renderer();
	~Renderer();

	Shader *getShader(std::string name);

	void	setShader(std::string name, Shader *shader);
};
