#pragma once


#include <iostream>
#include <vector>
#include <functional>

#include <SDL.h>

#include <glm.hpp>

enum BUTTON_STATE{
	BUTTON_DOWN,
	BUTTON_UP
};

typedef int (*MouseClickCallback)(int, int, int);

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);

	static InputHandler* Instance;

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
	
	bool listenRightClick(MouseClickCallback);
	bool listenLeftClick(MouseClickCallback);

private:
	SDL_Keycode keyDown;
	Uint32 mouseType;
	Uint32 mouseX;
	Uint32 mouseY;

	std::vector<MouseClickCallback> rightClickListeners;
	std::vector<MouseClickCallback> leftClickListeners;
};

