#include "TextureManager.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SOIL/SOIL.h>

#include <string>

GLuint		_tileset;
glm::vec2	_tileSize;
int			_xTextures;
int			_yTextures;

TextureManager::TextureManager(std::string path, int xTextures, int yTextures) : _xTextures(xTextures), _yTextures(yTextures) {
	_tileset = loadTexture(path);
	_tileSize = glm::vec2(1.0f / static_cast<GLfloat>(xTextures), 1.0f / static_cast<GLfloat>(yTextures));
}

TextureManager::~TextureManager() {
}

GLuint		TextureManager::getTileset() const {
	return _tileset;
}

glm::vec2	TextureManager::getTexturePos(int ID) const {
	int x = ID % _xTextures;
	int y = _yTextures - (ID / _xTextures + 1);

	return glm::vec2(x * _tileSize.x, y * _tileSize.y);
}

glm::vec2	TextureManager::getTexturePos(int block, int face) const {
	// E, W, T, B, S, N
	int blocks[] = {
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2,
	3, 3, 30, 3, 3, 3,
	4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7,
	8, 8, 8, 8, 8, 8,
	9, 9, 9, 9, 9, 9,
	10, 10, 10, 10, 10, 10,
	11, 11, 11, 11, 11, 11,
	12, 12, 12, 12, 12, 12,
	13, 13, 13, 13, 13, 13,
	14, 14, 14, 14, 14, 14,
	15, 15, 15, 15, 15, 15,
	16, 16, 16, 16, 16, 16,
	17, 17, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 18,
	19, 19, 19, 19, 19, 19,
	20, 20, 20, 20, 20, 20,
	21, 21, 21, 21, 21, 21,
	22, 22, 22, 22, 22, 22,
	23, 23, 23, 23, 23, 23,
	24, 24, 24, 24, 24, 24,
	25, 25, 25, 25, 25, 25,
	26, 26, 26, 26, 26, 26,
	27, 27, 27, 27, 27, 27,
	28, 28, 28, 28, 28, 28,
	30, 30, 30, 30, 30, 30,
	31, 31, 31, 31, 31, 31,
	1, 2, 3, 4, 5, 6,
	1, 2, 3, 4, 5, 6
	};

	return getTexturePos(blocks[block * 6 + face]);
}

glm::vec2	TextureManager::getTileSize() const {
	return _tileSize;
}

GLuint	TextureManager::loadTexture(std::string path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
