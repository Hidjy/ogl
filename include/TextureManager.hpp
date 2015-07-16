#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SOIL/SOIL.h>

#include <string>

class TextureManager {
private:
	GLuint		_tileset;
	int			_xTextures;
	int			_yTextures;

public:
	TextureManager(std::string path, int xTextures, int yTextures);
	~TextureManager();

	GLuint		getTileset() const;
	GLuint		getTexturePos(int block, int face) const;

	//TODO Register and Get texture per blockID:FACE pair.
	//TODO Texture Atlas Generator

	GLuint	loadTexture(std::string path);
};
