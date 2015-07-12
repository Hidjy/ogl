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
	glm::vec2	_tileSize;
	int			_xTextures;
	int			_yTextures;

public:
	TextureManager(std::string path, int xTextures, int yTextures);
	~TextureManager();

	GLuint		getTileset() const;
	glm::vec2	getTexturePos(int ID) const;
	glm::vec2	getTileSize() const;

	//TODO Register and Get texture per blockID:FACE pair.

	static GLuint	loadTexture(std::string path);
};
