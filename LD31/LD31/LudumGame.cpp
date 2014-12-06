#include "LudumGame.h"


LudumGame::LudumGame(void)
{
}


LudumGame::~LudumGame(void)
{
}

void LudumGame::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stdout, "Could not initialize SDL2\n");
		exit(1);
	}

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

	// initialize OpenGL
	glEnable(GL_TEXTURE_2D_ARRAY);
	glewExperimental = true;
	if(glewInit() != GLEW_OK)
	{
		fprintf(stdout, "Could not Initialize glew :(\n");
		exit(1);
	}

	glewGetExtension("GL_VERSION_3_3");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

}

void LudumGame::Update(float dt)
{}

void LudumGame::Render(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);


	SDL_GL_SwapWindow(window);

}

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
		case SDL_QUIT:
			{
				isRunning = false;
			}
			break;
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
