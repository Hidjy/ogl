#pragma once

 #define GLM_FORCE_RADIANS
// Std. Includes
#include <iostream>
#include <map>
#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// GL includes
#include "Shader.hpp"

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;	// Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;	// Horizontal offset to advance to next glyph
};

class TextManager {
public:
	std::map<GLchar, Character> _characters;
	GLuint _VAO, _VBO;
	Shader _shader;

	TextManager(int width, int height);
	~TextManager();

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};
