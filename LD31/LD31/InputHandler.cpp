#include "InputHandler.h"

InputHandler* InputHandler::Instance = nullptr;
InputHandler::InputHandler(void)
{
	this->mouseX = 0;
	this->mouseY = 0;
	Instance = this;
}


InputHandler::~InputHandler(void)
{
}

void InputHandler::evalKeyDown(SDL_Event& ev)
{
	//Check what key was pressed and act based on keypress
	this->keyDown = ev.key.keysym.sym;
}

void InputHandler::evalKeyUp(SDL_Event& ev)
{
	this->keyDown = NULL;
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
	//fprintf(stdout, "\n[!] Mouse motion, bro: (%d, %d)", this->mouseX, this->mouseY);
}

void InputHandler::evalMouseDown(SDL_Event& ev)
{
	this->mouseType = ev.button.type;
	//Mouse button was pressed, right click left click, amiright? We might have to tell someone the mouse clicked
	if(ev.button.button == SDL_BUTTON_LEFT)
	{
		fprintf(stdout, "\n[!] LEFT MOUSE DOWN!\n[=] X pos : %d\n[=] Y pos: %d\n",  this->mouseX, this->mouseY);
		for(auto i = leftClickListeners.begin(); i != leftClickListeners.end(); ++i)
		{
			(*i)(BUTTON_DOWN, mouseX, mouseY);
		}
	}
	if(ev.button.button == SDL_BUTTON_RIGHT)
	{
		fprintf(stdout, "\n[!] RIGHT MOUSE DOWN!\n[=] X pos : %d\n[=] Y pos: %d\n",  this->mouseX, this->mouseY);
	}

}

void InputHandler::evalMouseUp(SDL_Event& ev)
{
	this->mouseType = NULL;
}

SDL_Keycode InputHandler::getKeyDown()
{
	//Expect a key if the key is down, should be NULL otherwise
	return keyDown;
}

Uint32 InputHandler::curMouseX()
{
	return this->mouseX;
}

Uint32 InputHandler::curMouseY()
{
	return this->mouseY;
}

bool InputHandler::listenRightClick(MouseClickCallback ms)
{
	rightClickListeners.push_back(ms);
	return false;
}

bool InputHandler::listenLeftClick(MouseClickCallback ms)
{
	leftClickListeners.push_back(ms);
	return false;
}