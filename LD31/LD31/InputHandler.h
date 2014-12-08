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
		 
	void EvalKeyDown(SDL_Event& ev);
	void EvalKeyUp(SDL_Event& ev);
	void EvalWindowEvent(SDL_Event& ev);
	void EvalMouseMotion(SDL_Event& ev);
	void EvalMouseDown(SDL_Event& ev);
	void EvalMouseUp(SDL_Event& ev);
	glm::vec2 GetMousePos();
	Uint32 getMouseType();
	Uint32 GetMouseButton();
	SDL_Keycode GetKeyDown();
	
	bool ListenRightClick(MouseClickCallback);
	bool ListenLeftClick(MouseClickCallback);

private:
	SDL_Keycode keyDown;
	Uint32 mouseButton;
	glm::vec2 mousePos;

	std::vector<MouseClickCallback> rightClickListeners;
	std::vector<MouseClickCallback> leftClickListeners;
};

