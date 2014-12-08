#include "InputHandler.h"

InputHandler* InputHandler::Instance = nullptr;
InputHandler::InputHandler(void) : mouseButton(NULL)
{
	Instance = this;
}


InputHandler::~InputHandler(void)
{
}

void InputHandler::EvalKeyDown(SDL_Event& ev)
{
	//Check what key was pressed and act based on keypress
	this->keyDown = ev.key.keysym.sym;
}

void InputHandler::EvalKeyUp(SDL_Event& ev)
{
	this->keyDown = NULL;
}

void InputHandler::EvalWindowEvent(SDL_Event& ev)
{
	//Check what window event occured, act accordingly
}

void InputHandler::EvalMouseMotion(SDL_Event& ev)
{
	//Track the mouse, cursor action? We might have to tell someone that the mouse moved
	//this->mouseX = ev.motion.x;
	//this->mouseY = ev.motion.y;
	mousePos.x = ev.motion.x;
	mousePos.y = ev.motion.y;
	//fprintf(stdout, "\n[!] Mouse motion, bro: (%d, %d)", this->mouseX, this->mouseY);
}

void InputHandler::EvalMouseDown(SDL_Event& ev)
{
	this->mouseButton = ev.button.button;
	//Mouse button was pressed, right click left click, amiright? We might have to tell someone the mouse clicked
	if(ev.button.button == SDL_BUTTON_LEFT)
	{
		fprintf(stdout, "\n[!] LEFT MOUSE DOWN!\n[=] X pos : %d\n[=] Y pos: %d",  this->mousePos.x, this->mousePos.y);
	}
	if(ev.button.button == SDL_BUTTON_RIGHT)
	{
		fprintf(stdout, "\n[!] RIGHT MOUSE DOWN!\n[=] X pos : %d\n[=] Y pos: %d",  this->mousePos.x, this->mousePos.y);
	}

}

Uint32 InputHandler::GetMouseButton()
{
	return mouseButton;
}

void InputHandler::EvalMouseUp(SDL_Event& ev)
{
	this->mouseButton = NULL;
}

SDL_Keycode InputHandler::GetKeyDown()
{
	//Expect a key if the key is down, should be NULL otherwise
	return keyDown;
}

glm::vec2 InputHandler::GetMousePos()
{
	return mousePos;
}