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

static void getSubData(unsigned char *src, unsigned char *dst, int xbegin, int ybegin, int xsize, int ysize, int srcWidth)
{
	for (int x = 0; x < xsize; x++) {
		for (int y = 0; y < ysize; y++) {
			dst[(x + y * xsize) * 3] = src[((x + xbegin) + (y + ybegin) * srcWidth) * 3 ];
			dst[(x + y * xsize) * 3 + 1] = src[((x + xbegin) + (y + ybegin) * srcWidth) * 3 + 1];
			dst[(x + y * xsize) * 3 + 2] = src[((x + xbegin) + (y + ybegin) * srcWidth) * 3 + 2];
		}
	}
}

GLuint	TextureManager::loadTexture(std::string path) {
	int width, height;
	// unsigned char* image = SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGB);

	// int textureWidth = width / _xTextures;
	// int textureHeight = height / _yTextures;
	// int nbTextures = _xTextures * _yTextures;

	std::string paths[] = {
	"ressources/0.png",
	"ressources/1.png",
	"ressources/2.png",
	"ressources/3.png",
	"ressources/4.png",
	"ressources/5.png",
	"ressources/6.png",
	"ressources/7.png",
	"ressources/8.png",
	"ressources/9.png",
	"ressources/10.png",
	"ressources/11.png",
	"ressources/12.png",
	"ressources/13.png",
	"ressources/14.png",
	"ressources/15.png",
	"ressources/16.png",
	"ressources/17.png",
	"ressources/18.png",
	"ressources/19.png",
	"ressources/20.png",
	"ressources/21.png",
	"ressources/22.png",
	"ressources/23.png",
	"ressources/24.png",
	"ressources/25.png",
	"ressources/26.png",
	"ressources/27.png",
	"ressources/28.png",
	"ressources/29.png",
	"ressources/30.png",
	"ressources/31.png",
	};

	int textureWidth = 16;
	int textureHeight = 16;
	int nbTextures = 32;

	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY,texture);
	//Allocate the storage.
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGB8, textureWidth, textureHeight, nbTextures);
	//Upload pixel data.
	// for (int x = 0; x < _xTextures; x++) {
	// 	for (int y = 0; y < _yTextures; y++) {
	// 		unsigned char sub[textureWidth * textureHeight * 3];
	// 		getSubData(image, sub, x * textureWidth, y * textureHeight, textureWidth, textureHeight, width);
	// 		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, x + y * _xTextures, textureWidth, textureHeight, 1, GL_RGB, GL_UNSIGNED_BYTE, sub);
	// 	}
	// }

	for (int i = 0; i < nbTextures; i++) {
			unsigned char* image = SOIL_load_image(paths[i].data(), &width, &height, 0, SOIL_LOAD_RGB);
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, textureWidth, textureHeight, 1, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
	}

	//Always set reasonable texture parameters
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	//glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);

	// SOIL_free_image_data(image);

	return texture;
}
