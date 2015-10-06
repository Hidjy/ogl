#pragma once

#include <map>
#include <string>

#include "Shader.hpp"
#include "TextureManager.hpp"

class Renderer {
private:
	std::map<std::string, Shader *>	_shaders;

	TextureManager *_textureManager;

public:
	Renderer();
	~Renderer();

	Shader *getShader(std::string name);

	TextureManager *getTextureManager();

	void	setShader(std::string name, Shader *shader);

	void	setTextureManager(TextureManager *TextureManager);

};
