#include "InputHandler.h"


InputHandler::InputHandler(void)
{
	this->mouseX = 0;
	this->mouseY = 0;
}


InputHandler::~InputHandler(void)
{
}

void InputHandler::evalKeyDown(SDL_Event& ev)
{
		//Check what key was pressed and act based on keypress
}

void InputHandler::evalWindowEvent(SDL_Event& ev)
{
	//Check what window event occured, act accordingly
}

void InputHandler::evalMouseMotion(SDL_Event& ev)
{
	//Track the mouse, cursor action? We might have to tell someone that the mouse moved
	this->mouseX = ev.motion.x;
	this->mouseY = ev.motion.y;
	fprintf(stdout, "\n[!] Mouse motion, bro: (%d, %d)", this->mouseX, this->mouseY);
}

void InputHandler::evalMouseButton(SDL_Event& ev)
{
	//Mouse button was pressed, right click left click, amiright? We might have to tell someone the mouse clicked
	if(ev.button.button == SDL_BUTTON_LEFT)
	{
		fprintf(stdout, "\n[!] LEFT MOUSE CLICK!\n[=] X pos : %d\n[=] Y pos: %d",  this->mouseX, this->mouseY);
	}
	if(ev.button.button == SDL_BUTTON_RIGHT)
	{
		fprintf(stdout, "\n[!] RIGHT MOUSE CLICK!\n[=] X pos : %d\n[=] Y pos: %d",  this->mouseX, this->mouseY);
	}

}

int InputHandler::curMouseX()
{
	return this->mouseX;
}

int InputHandler::curMouseY()
{
	return this->mouseY;
}