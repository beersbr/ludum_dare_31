#pragma once

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Entity.h"
#include "InputHandler.h"
#include "ShaderProgram.h"

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
	int getMouseX;
	int getMouseY;
	void Run();

public:
	std::string WindowTitle;
	unsigned int ViewportWidth;
	unsigned int ViewportHeight;

	SDL_Window* window;
	SDL_GLContext context;
	bool isRunning;

private:
	InputHandler inputKing;

	GLuint VAO; // vertex array object :: OpenGL

};

