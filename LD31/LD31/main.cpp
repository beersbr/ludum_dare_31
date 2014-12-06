#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[])
{
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("TITLE", 0, 0, 100, 100, 0);

	return 0;
}