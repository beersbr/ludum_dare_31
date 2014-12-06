#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

#include <SDL_opengl.h>

class ShaderProgram
{
public:
	ShaderProgram(void);
	~ShaderProgram(void);

public:
	GLuint shaderID;

	static std::map<std::string, ShaderProgram> shaders;
};

