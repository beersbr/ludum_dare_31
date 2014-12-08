#include "InputHandler.h"

InputHandler* InputHandler::instance = nullptr;

InputHandler* InputHandler::Instance()
{
	if(InputHandler::instance == nullptr)
		InputHandler::instance = new InputHandler();
	return InputHandler::instance;
}


InputHandler::InputHandler(void) : mouseButton(NULL)
{
	mousePos = glm::vec2(0.0, 0.0);
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
		//fprintf(stdout, "\n[!] LEFT MOUSE DOWN!\n[=] X pos : %f\n[=] Y pos: %f\n",  this->mousePos.x, this->mousePos.y);

	}
	if(ev.button.button == SDL_BUTTON_RIGHT)
	{
		//fprintf(stdout, "\n[!] RIGHT MOUSE DOWN!\n[=] X pos : %f\n[=] Y pos: %f",  this->mousePos.x, this->mousePos.y);
	}

}

Uint32 InputHandler::GetMouseButton()
{
	return mouseButton;
}

void InputHandler::EvalMouseUp(SDL_Event& ev)
{
	this->mouseButton = ev.button.button;
	//Mouse button was pressed, right click left click, amiright? We might have to tell someone the mouse clicked
	MouseClick ms = { mousePos, mouseButton };
	if(ev.button.button == SDL_BUTTON_LEFT)
	{
		//fprintf(stdout, "\n[!] LEFT MOUSE UP!\n[=] X pos : %f\n[=] Y pos: %f\n",  this->mousePos.x, this->mousePos.y);

	}
	if(ev.button.button == SDL_BUTTON_RIGHT)
	{
		//fprintf(stdout, "\n[!] RIGHT MOUSE UP!\n[=] X pos : %f\n[=] Y pos: %f",  this->mousePos.x, this->mousePos.y);
	}
	mouseClicks.push_back(ms);
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

std::vector<MouseClick> InputHandler::GetMouseClicks()
{
	return mouseClicks;
}

void InputHandler::ResetMouseClicks()
{
	mouseClicks.erase(mouseClicks.begin(), mouseClicks.end());
}
