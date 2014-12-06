#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <SDL_opengl.h>

class ShaderProgram
{
public:
	ShaderProgram(void);
	~ShaderProgram(void);

	static bool CompileShader(ShaderProgram shader, const bool debug = false);
	static std::string ReadFile(std::string const filePath);

public:
	GLuint shaderID;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	std::string vertexShaderPath;
	std::string fragmentShaderPath;

	static std::map<std::string, ShaderProgram> shaders;
};

