#pragma once

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Entity.h"

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

public:
	std::string WindowTitle;
	unsigned int ViewportWidth;
	unsigned int ViewportHeight;

	SDL_Window* window;
	SDL_GLContext context;
	bool isRunning;

};

