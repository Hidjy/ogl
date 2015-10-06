#include "Shader.hpp"
#include <iostream>
#include <fstream>

Shader::Shader(void)
{
	_totalShaders=0;
	_shaders[VERTEX_SHADER]=0;
	_shaders[FRAGMENT_SHADER]=0;
	_shaders[GEOMETRY_SHADER]=0;
	_attributeList.clear();
	_uniformLocationList.clear();
}

Shader::~Shader(void)
{
	_attributeList.clear();
	_uniformLocationList.clear();
}

void Shader::loadFromString(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader (type);

	const char * ptmp = source.c_str();
	glShaderSource (shader, 1, &ptmp, NULL);

	//check whether the shader loads fine
	GLint status;
	glCompileShader (shader);
	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog= new GLchar[infoLogLength];
		glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
		std::cerr << "Compile log: " << infoLog << std::endl;
		delete [] infoLog;
	}
	_shaders[_totalShaders++]=shader;
}


void Shader::createAndLinkProgram() {
	_program = glCreateProgram ();
	if (_shaders[VERTEX_SHADER] != 0) {
		glAttachShader (_program, _shaders[VERTEX_SHADER]);
	}
	if (_shaders[FRAGMENT_SHADER] != 0) {
		glAttachShader (_program, _shaders[FRAGMENT_SHADER]);
	}
	if (_shaders[GEOMETRY_SHADER] != 0) {
		glAttachShader (_program, _shaders[GEOMETRY_SHADER]);
	}

	//link and check whether the program links fine
	GLint status;
	glLinkProgram (_program);
	glGetProgramiv (_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;

		glGetProgramiv (_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog= new GLchar[infoLogLength];
		glGetProgramInfoLog (_program, infoLogLength, NULL, infoLog);
		std::cerr << "Link log: " << infoLog << std::endl;
		delete [] infoLog;
	}

	glDeleteShader(_shaders[VERTEX_SHADER]);
	glDeleteShader(_shaders[FRAGMENT_SHADER]);
	glDeleteShader(_shaders[GEOMETRY_SHADER]);
}

void Shader::use() {
	glUseProgram(_program);
}

void Shader::unUse() {
	glUseProgram(0);
}

void Shader::addAttribute(const std::string& attribute) {
	_attributeList[attribute]= glGetAttribLocation(_program, attribute.c_str());
}

//An indexer that returns the location of the attribute
GLuint Shader::operator [](const std::string& attribute) {
	return _attributeList[attribute];
}

void Shader::addUniform(const std::string& uniform) {
	_uniformLocationList[uniform] = glGetUniformLocation(_program, uniform.c_str());
}

GLuint Shader::operator()(const std::string& uniform){
	return _uniformLocationList[uniform];
}
GLuint Shader::getProgram() const {
	return _program;
}

void Shader::loadFromFile(GLenum whichShader, const std::string& filename){
	std::ifstream fp;
	fp.open(filename.c_str(), std::ios_base::in);
	if(fp) {
		std::string buffer(std::istreambuf_iterator<char>(fp), (std::istreambuf_iterator<char>()));
		loadFromString(whichShader, buffer);
	} else {
		std::cerr << "Error loading shader: " << filename << std::endl;
	}
}

void Shader::deleteProgram() {
	glDeleteProgram(_program);
	_program=-1;
}
