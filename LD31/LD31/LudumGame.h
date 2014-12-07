#pragma once

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Util.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Loader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "World.h"

class LudumGame
{
public:
	LudumGame(void);
	~LudumGame(void);

	void Init();
	void Update(float dt);
	void Render(float dt);
	void Cleanup();
	void HandleEvents();
	void Run();

	// test 
	Mesh *MeshTest(std::string path = "assets/snowman1-sprite.png");


public:
	std::string WindowTitle;
	unsigned int ViewportWidth;
	unsigned int ViewportHeight;

	SDL_Window* window;
	SDL_GLContext context;
	bool isRunning;

	Mesh *m;
	Mesh *m2;

	World *world;

private:
	InputHandler inputKing;
	Loader* loaderKing;

	GLuint VAO; // vertex array object :: OpenGL
};

