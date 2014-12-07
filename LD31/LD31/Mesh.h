#pragma once

#include <vector>
#include <map>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "ShaderProgram.h"

// these represent layout positions in the shader
enum SHADER { 
	position = 0,
	color,
	normal,
	uv
};

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	void Render(glm::mat4 const projection, glm::mat4 const view, glm::vec3 const lightDir);

public:
	glm::mat4 transform;

	std::vector<glm::vec3> v; // verts
	std::vector<glm::vec3> c; // colors
	std::vector<glm::vec3> n; // normals
	std::vector<glm::vec2> t; // texutre coords
	std::vector<std::vector<glm::vec2> > animation;
	unsigned int frame;

	std::vector<GLubyte>   e; // elements

	GLuint renderMethod;

	GLuint textureID;

	ShaderProgram *shader;
};

