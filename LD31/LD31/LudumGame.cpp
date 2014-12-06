#include "LudumGame.h"


LudumGame::LudumGame(void)
{
}


LudumGame::~LudumGame(void)
{
}

void LudumGame::Init()
{
	isRunning = true;
	ViewportWidth = 1200;
	ViewportHeight = 800; 

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(WindowTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		ViewportWidth,
		ViewportHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	context = SDL_GL_CreateContext(window);

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

void LudumGame::Run()
{
	Init();

	while(isRunning)
	{
		// TODO: Time stuff

		float dt = 0.0f;

		HandleEvents();
		Update(dt);
		Render(dt);


	}

	Cleanup();
}
