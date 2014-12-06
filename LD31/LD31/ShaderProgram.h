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
	~ShaderProgram(void);

	static ShaderProgram* CreateShader(std::string name, std::string vertexPath, std::string fragmentPath);
	static bool CompileShader(ShaderProgram *shader, const bool forceRecompile = false);
	static std::string ReadFile(std::string const filePath);

public:
	GLuint shaderID;

	std::string vertexShaderPath;
	std::string fragmentShaderPath;

	static std::map<std::string, ShaderProgram*> shaders;

private:
	static bool ShaderExists(std::string name);

	ShaderProgram(void);

private:
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
};

