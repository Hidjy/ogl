#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "RenderContext.hpp"

class		Mesh {
private:
	GLenum		_mode;

	GLuint		_VAO;
	GLuint		_VBO;
	GLuint		_instancedVBO;
	GLuint		_EBO;

	GLfloat			*_vertexBuffer;
	unsigned int	_vertexBufferSize;

	GLfloat			*_instanceBuffer;
	unsigned int	_instanceBufferSize;

	GLuint			*_elementBuffer;
	unsigned int	_elementBufferSize;

public:
	Mesh();
	~Mesh();

	void	setMode(GLenum mode);

	void	setVertexBuffer(GLfloat *buffer, unsigned int size);
	void	setInstanceBuffer(GLfloat *buffer, unsigned int size);
	void	setElementBuffer(GLuint *buffer, unsigned int size);

	GLfloat		*getVertexBuffer(void);
	GLfloat		*getInstanceBuffer(void);
	GLuint		*getElementBuffer(void);

	void	render(RenderContext *renderContext);
	void	render(RenderContext *renderContext, unsigned int instances);
};
