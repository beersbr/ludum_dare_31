#pragma once

#include <SDL.h>
#include <glm.hpp>
#include <iostream>

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
	Uint32 GetMouseButton();
	SDL_Keycode GetKeyDown();
private:
	SDL_Keycode keyDown;
	Uint32 mouseButton;
	glm::vec2 mousePos;

};

