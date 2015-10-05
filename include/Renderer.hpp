#pragma once

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
