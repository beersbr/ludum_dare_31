#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include <SDL.h>
#include <glm.hpp>

struct {
	glm::vec2 pos;
	Uint8 sdl_button;
} typedef MouseClick;

class InputHandler
{
public:
	
	~InputHandler(void);
	static InputHandler* Instance();
	
		 
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

	std::vector<MouseClick> GetMouseClicks();
	void ResetMouseClicks();

private:
	InputHandler(void);
	static InputHandler* instance;


	SDL_Keycode keyDown;
	Uint32 mouseButton;
	glm::vec2 mousePos;

	std::vector<MouseClick> mouseClicks;
};

