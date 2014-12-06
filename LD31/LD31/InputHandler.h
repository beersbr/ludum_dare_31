#pragma once

#include <SDL.h>
#include <iostream>

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);
	void evalKeyDown(SDL_Event& ev);
	void evalWindowEvent(SDL_Event& ev);
	void evalMouseMotion(SDL_Event& ev);
	void evalMouseButton(SDL_Event& ev);
	int curMouseX();
	int curMouseY();

private:
	int mouseX;
	int mouseY;
};

