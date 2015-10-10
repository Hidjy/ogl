#pragma once

#include <map>
#include <string>

#include "Shader.hpp"

class ShaderManager {
private:
	std::map<std::string, Shader *>	_shaders;

public:
	ShaderManager();
	~ShaderManager();

	Shader *getShader(std::string name);

	void	setShader(std::string name, Shader *shader);
};
