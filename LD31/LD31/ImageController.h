#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class ImageController
{
public:
	static ImageController* Instance();
	~ImageController(void);

	void Load(SDL_Renderer* r, std::string name, std::string const path);

	SDL_Surface* GetSurface(std::string tag);
	SDL_Texture* GetTexture(std::string tag);

protected:
	static ImageController* instance;

	ImageController();

	std::map<std::string, SDL_Surface*> surfaces;
	std::map<std::string, SDL_Texture*> textures;
};

