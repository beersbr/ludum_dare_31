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
		fprintf(stdout, "ERROR: Could not initialize SDL2.\n");
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

	SDL_GL_SetSwapInterval(1);

	// initialize OpenGL
	glEnable(GL_TEXTURE_2D_ARRAY);
	glewExperimental = true;
	if(glewInit() != GLEW_OK)
	{
		fprintf(stdout, "ERROR: Could not Initialize glew.\n");
		isRunning = false;
		return;
	}

	glewGetExtension("GL_VERSION_3_3");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Game Loading
	this->loaderKing = new Loader();

	glGenVertexArrays(1, &VAO);
	if(VAO < 0)
	{
		fprintf(stdout, "ERROR: Could not get a VAO for opengl\n");
		isRunning = false;
		return;
	}

	glBindVertexArray(VAO);

	ShaderProgram::CreateShader("main", "main_vertex.glsl", "main_fragment.glsl");
}

void LudumGame::Update(float dt)
{
	// TODO: Check input and run relevent component methods
}

void LudumGame::Render(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.0f, 0.3f, 1.0f);

	MeshTest();

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
		case SDL_KEYDOWN:
			{
				this->inputKing.evalKeyDown(event);
				break;
			}
		case SDL_KEYUP:
			{
				this->inputKing.evalKeyUp(event);
				break;
			}
		case SDL_WINDOWEVENT:
			{
				this->inputKing.evalWindowEvent(event);
				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			{
				this->inputKing.evalMouseDown(event);
				break;
			}
		case SDL_MOUSEBUTTONUP:
			{
				this->inputKing.evalMouseUp(event);
				break;
			}
		case SDL_MOUSEMOTION:
			{
				this->inputKing.evalMouseMotion(event);
				break;
			}
		default:
			{
				//Whoever put this in, is an idiot
				//fprintf(stdout, "EVENT TYPE: %d\n", event.type);
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


/*********************************************
TEST FUNCTIONS
**********************************************/
void LudumGame::MeshTest()
{
	float hvw = static_cast<float>(ViewportWidth/2);
	float hvh = static_cast<float>(ViewportHeight/2);

	glm::mat4 Projection = glm::ortho(-hvw, hvw, -hvh, hvh, 500.0f, -500.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0, 0.0, 500.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0)
		);

	Mesh m;

	m.transform = glm::scale(m.transform, glm::vec3(100.0, 100.0, 100.0));

	// vertices
	/*
		0 -- 2
		|    |
		1 -- 3
	*/
	m.v.push_back(glm::vec3(-1.0,  1.0,  0.0));
	m.v.push_back(glm::vec3(-1.0, -1.0,  0.0));
	m.v.push_back(glm::vec3( 1.0,  1.0,  0.0));
	m.v.push_back(glm::vec3( 1.0, -1.0,  0.0));

	// colors
	m.c.push_back(glm::vec3( 0.0,  0.0,  0.0));
	m.c.push_back(glm::vec3( 0.0,  0.0,  0.0));
	m.c.push_back(glm::vec3( 0.0,  0.0,  0.0));
	m.c.push_back(glm::vec3( 0.0,  0.0,  0.0));

	// normals
	m.n.push_back(glm::vec3( 0.0,  0.0,  1.0));
	m.n.push_back(glm::vec3( 0.0,  0.0,  1.0));
	m.n.push_back(glm::vec3( 0.0,  0.0,  1.0));
	m.n.push_back(glm::vec3( 0.0,  0.0,  1.0));

	// elements
	m.e.push_back(0);
	m.e.push_back(1);
	m.e.push_back(2);
	m.e.push_back(2);
	m.e.push_back(1);
	m.e.push_back(3);

	m.Render(Projection, View, glm::vec3(1.0, 1.0, 1.0));
}