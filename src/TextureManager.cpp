#include "TextureManager.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <SOIL/SOIL.h>

#include <string>

TextureManager::TextureManager(std::string path, int xTextures, int yTextures) : _xTextures(xTextures), _yTextures(yTextures) {
	_tileset = loadTexture(path);
}

TextureManager::~TextureManager() {
}

GLuint		TextureManager::getTileset() const {
	return _tileset;
}

GLuint		TextureManager::getTexturePos(int block, int face) const {
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

	return blocks[block * 6 + face];
}

GLuint	TextureManager::loadTexture(std::string path) {
	int width, height;
	unsigned char* image = SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGB);

	int textureWidth = width / _xTextures;
	int textureHeight = height / _yTextures;
	int nbTextures = _xTextures * _yTextures;

	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY,texture);
	//Allocate the storage.
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGB8, textureWidth, textureHeight, nbTextures);
	//Upload pixel data.
	for (int x = 0; x < _xTextures; x++) {
		for (int y = 0; y < _yTextures; y++) {
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, x * textureWidth, y * textureHeight, x + y * x, textureWidth, textureHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
	}

	//Always set reasonable texture parameters
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(image);

	return texture;
}
