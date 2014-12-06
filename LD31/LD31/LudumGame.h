#pragma once

#include <iostream>

#include <SDL.h>


class LudumGame
{
public:
	LudumGame(void);
	~LudumGame(void);

	void Update();
	void Render();
	void Cleanup();
	void HandleEvents();

public:
	SDL_Window* window;
};

