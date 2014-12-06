#include "LudumGame.h"


LudumGame::LudumGame(void)
{
}


LudumGame::~LudumGame(void)
{
}

void LudumGame::Update()
{}

void LudumGame::Render()
{}

void LudumGame::Cleanup()
{}

void LudumGame::HandleEvents()
{
	SDL_Event event;
	SDL_memset(&event, 0, sizeof(SDL_Event));

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		default:
			{
				fprintf(stdout, "EVENT TYPE: %d\n", event.type);
			}
		}
	}
}