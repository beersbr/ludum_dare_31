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

	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow(WindowTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		ViewportWidth,
		ViewportHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	context = SDL_GL_CreateContext(window);
	//glEnable(GL_TEXTURE_2D);
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		fprintf(stdout, "ERROR: Could not Initialize glew.\n");
		isRunning = false;
		return;
	}

	// so that we can load jpgs
	//IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//SDL_GL_SetSwapInterval(1);

	// initialize OpenGL
	//glEnable(GL_TEXTURE_2D_ARRAY);

	int err1 = glGetError();
	int sup = glewGetExtension("GL_VERSION_3_3");
	
	int err2 = glGetError();
	
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.6f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
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
	m = MeshTest();
	m->transform = glm::translate(m->transform, glm::vec3(-100.0, 0.0, 0.0));
	m->transform = glm::scale(m->transform, glm::vec3(400, 400, 1));
	m->transform = glm::rotate(m->transform, 90.0f, glm::vec3(0.0, 0.0, 1.0));

	m2 = MeshTest("assets/snowman2-sprite.png");
	m2->transform = glm::translate(m2->transform, glm::vec3(100.0, 0.0, 0.0));
	m2->transform = glm::scale(m2->transform, glm::vec3(400.0, 400.0, 1.0));
	m2->transform = glm::rotate(m2->transform, -90.0f, glm::vec3(0.0, 0.0, 1.0));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// load images that we might need and tag them
	// TODO: this should be put in a json and given to us by the loader as a list of tags and paths
	ImageController::Instance()->Load(renderer, "snowman1", "assets/snowman1-sprite.png");
	ImageController::Instance()->Load(renderer, "snowman2", "assets/snowman2-sprite.png");
	ImageController::Instance()->Load(renderer, "blood-snow1", "assets/blood-snow-1.jpg");
	ImageController::Instance()->Load(renderer, "projectile-tower", "assets/projectile-tower.png");

	world = new World(nullptr);
	world->CreateMap(renderer);
}

void LudumGame::Update(float dt)
{
	world->Update(dt);
	// TODO: Check input and run relevent component methods
}

void LudumGame::Render(float dt)
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.0f, 0.3f, 1.0f);*/

	float hvw = static_cast<float>(ViewportWidth/2);
	float hvh = static_cast<float>(ViewportHeight/2);

	SDL_RenderClear(renderer);
	world->RenderMap(renderer, dt);
	SDL_RenderPresent(renderer);
}

void LudumGame::Cleanup()
{
	IMG_Quit();
}

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
				this->inputKing.EvalKeyDown(event);
				break;
			}
		case SDL_KEYUP:
			{
				this->inputKing.EvalKeyUp(event);
				break;
			}
		case SDL_WINDOWEVENT:
			{
				this->inputKing.EvalWindowEvent(event);
				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			{
				this->inputKing.EvalMouseDown(event);
				break;
			}
		case SDL_MOUSEBUTTONUP:
			{
				this->inputKing.EvalMouseUp(event);
				break;
			}
		case SDL_MOUSEMOTION:
			{
				this->inputKing.EvalMouseMotion(event);
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

	unsigned int frames = 1;

	unsigned int start = SDL_GetTicks();
	unsigned int lastTime = start;
	unsigned int time = start;

	unsigned int timer = 0;

	while(isRunning)
	{
		unsigned int lastTime = time;
		time = SDL_GetTicks();
		unsigned int elapsedTime = time - lastTime;


		float t = (time - start)/1000;
		float FPS = frames/(std::max(t, 0.000001f));

		if(FPS < 10.0f && SDL_GetTicks() - start > 10000)
		{
			fprintf(stdout, "WARNING: FPS DROPPING: %f\n", FPS);
			//getchar();
			break;
		}

		if(timer > 1000)
		{
			fprintf(stdout, "FPS: %lf -- %lf\n", FPS, elapsedTime/1000.0f);

			timer = 0;
		}

		double dt = elapsedTime/1000.0f;

		HandleEvents();
		Update(dt);
		Render(dt);

		++frames;

		timer += elapsedTime;
	}

	Cleanup();
}


/*********************************************
TEST FUNCTIONS
**********************************************/
Mesh* LudumGame::MeshTest(std::string path)
{
	float hvw = static_cast<float>(ViewportWidth/2);
	float hvh = static_cast<float>(ViewportHeight/2);

	glm::mat4 Projection = glm::ortho(-hvw, hvw, -hvh, hvh, 500.0f, -500.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0, 0.0, 500.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0)
		);

	Mesh *m = new Mesh();
	/*m->transform = glm::scale(m->transform, glm::vec3(40.0, 40.0, 1.0));*/
	SDL_Surface* surface = IMG_Load(path.c_str());

	// vertices
	/*
		0 -- 2
		|    |
		1 -- 3
	*/
	m->v.push_back(glm::vec3(-1.0,  1.0,  0.0));
	m->v.push_back(glm::vec3(-1.0, -1.0,  0.0));
	m->v.push_back(glm::vec3( 1.0,  1.0,  0.0));
	m->v.push_back(glm::vec3( 1.0, -1.0,  0.0));

	// colors
	m->c.push_back(glm::vec3( 0.0,  0.0,  0.0));
	m->c.push_back(glm::vec3( 0.0,  0.0,  0.0));
	m->c.push_back(glm::vec3( 0.0,  0.0,  0.0));
	m->c.push_back(glm::vec3( 0.0,  0.0,  0.0));

	// normals
	m->n.push_back(glm::vec3( 0.0,  0.0,  1.0));
	m->n.push_back(glm::vec3( 0.0,  0.0,  1.0));
	m->n.push_back(glm::vec3( 0.0,  0.0,  1.0));
	m->n.push_back(glm::vec3( 0.0,  0.0,  1.0));


	// frames
	std::vector<glm::vec2> frame1;
	frame1.push_back(glm::vec2( 0.0,  0.0));
	frame1.push_back(glm::vec2( 0.0,  0.5));
	frame1.push_back(glm::vec2( 0.25,  0.0));
	frame1.push_back(glm::vec2( 0.25,  0.5));

	std::vector<glm::vec2> frame2;
	frame2.push_back(glm::vec2( 0.25,  0.0));
	frame2.push_back(glm::vec2( 0.25,  0.5));
	frame2.push_back(glm::vec2( 0.50,  0.0));
	frame2.push_back(glm::vec2( 0.50,  0.5));

	std::vector<glm::vec2> frame3;
	frame3.push_back(glm::vec2( 0.50,  0.0));
	frame3.push_back(glm::vec2( 0.50,  0.5));
	frame3.push_back(glm::vec2( 0.75,  0.0));
	frame3.push_back(glm::vec2( 0.75,  0.5));

	std::vector<glm::vec2> frame4;
	frame4.push_back(glm::vec2( 0.75,  0.0));
	frame4.push_back(glm::vec2( 0.75,  0.5));
	frame4.push_back(glm::vec2( 1.0,  0.0));
	frame4.push_back(glm::vec2( 1.0,  0.5));

	m->animation.push_back(frame1);
	m->animation.push_back(frame2);
	m->animation.push_back(frame3);
	m->animation.push_back(frame4);

	m->frame = 0;
	m->t = m->animation[m->frame];

	m->textureID = SDL_SurfaceToTexture(surface);

	// elements
	m->e.push_back(0);
	m->e.push_back(1);
	m->e.push_back(2);
	m->e.push_back(2);
	m->e.push_back(1);
	m->e.push_back(3);

	return m;
}