#include "ImageController.h"

ImageController* ImageController::instance = nullptr;

ImageController* ImageController::Instance()
{
	if(ImageController::instance == nullptr)
		ImageController::instance = new ImageController();

	return ImageController::instance;
}

ImageController::ImageController(void)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}


ImageController::~ImageController(void)
{

	// free all the assets
}


void ImageController::Load(SDL_Renderer* r, std::string name, std::string const path)
{
	SDL_Surface* s = IMG_Load(path.c_str());
	if(!s)
	{
		fprintf(stdout, "WARNING: Could not load image: %s\n", path.c_str());
		return;
	}

	SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
	if(!t)
	{
		fprintf(stdout, "WARNING: Could not create texture for surface: %s\n", path.c_str());
		return;
	}

	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);
	surfaces[name] = s;

	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	textures[name] = t;

	return;
}

SDL_Surface* ImageController::GetSurface(std::string tag)
{
	return (surfaces[tag]);
}

SDL_Texture* ImageController::GetTexture(std::string tag)
{
	return (textures[tag]);
}