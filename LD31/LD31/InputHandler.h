#pragma once

#include <SDL.h>
#include <iostream>

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);
	void evalKeyDown(SDL_Event& ev);
	void evalKeyUp(SDL_Event& ev);
	void evalWindowEvent(SDL_Event& ev);
	void evalMouseMotion(SDL_Event& ev);
	void evalMouseDown(SDL_Event& ev);
	void evalMouseUp(SDL_Event& ev);
	Uint32 curMouseX();
	Uint32 curMouseY();
	Uint32 getMouseType();
	SDL_Keycode getKeyDown();
private:
	SDL_Keycode keyDown;
	Uint32 mouseType;
	Uint32 mouseX;
	Uint32 mouseY;
};

