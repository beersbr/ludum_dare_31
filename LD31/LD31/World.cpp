#include "World.h"


World::World(Loader* loader)
{
	this->loaderKing = loader;
}


World::~World(void)
{

}


bool World::createTowerEntity(std::string entityName)
{
	//see if the loader has the props to create an entity
	std::stringstream ss;
	// How/what/where/when do we create bullets?
	// We should probably do it when the tower updates, but the tower needs a reference to the world?

	std::map<std::string, std::string>* towerProps = loaderKing->getTowerEntityProps(entityName);
	if(!towerProps)
	{
		ss << "[-] Failed to load tower entity: " << entityName << "\n";
		fprintf(stdout, ss.str().c_str());
		return false;
	}
	//Create the tower using these props
	entities.push_back(new TowerEntity(&this->entities, towerProps));

	return true;
}

bool World::createEnemyEntity(std::string entityName)
{
	//see if the loader has the props to create an entity
	std::stringstream ss;
	// How/what/where/when do we create bullets?
	// We should probably do it when the tower updates, but the tower needs a reference to the world?

	std::map<std::string, std::string>* enemyProps = loaderKing->getEnemyEntityProps(entityName);
	if(!enemyProps)
	{
		ss << "[-] Failed to load enemy entity: " << entityName << "\n";
		fprintf(stdout, ss.str().c_str());
		return false;
	}
	//Create the tower using these props
	entities.push_back(new TowerEntity(&this->entities, enemyProps));

	return true;
}


bool World::createTileAtPos(glm::vec2 const pos)
{
	// TOOD: this needs to be moved to a config


	return false;
}


bool World::createMap(SDL_Renderer* r)
{
	int mapWidth = 1200;
	int mapHeight = 800;

	surface = SDL_CreateRGBSurface(0, 1200, 800, 32, 0, 0, 0, 0);

	SDL_Surface* tile = IMG_Load("assets/snow-tile.jpg");
	SDL_Rect tileSize = {0, 0, 40, 40};

	for(int y = 0; y < mapHeight; y+=40)
	{
		for(int x = 0; x < mapWidth; x += 40)
		{
			SDL_Rect dst = {x, y, 40, 40};
			SDL_BlitSurface(tile, &tileSize, surface, &dst);
		}
	}

	texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_SetTextureBlendMode(texture,
		SDL_BLENDMODE_BLEND);

	SDL_Surface* s = SDL_CreateRGBSurface(0, 40, 40, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_Rect rect = {0, 0, 40, 40};
	SDL_FillRect(s, &rect, 0xFF000033);
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);


	hoverTexture = SDL_CreateTextureFromSurface(r, s);

	SDL_SetTextureBlendMode(hoverTexture, SDL_BLENDMODE_BLEND);

	return false;
}


glm::vec2 World::getPos(int index)
{
	glm::vec2 pos;
	pos.y = std::floor(index/(800/40));
	pos.x = index%(1200/40);

	return pos;
}

glm::vec2 World::getTileCoord(int x = -1, int y = -1)
{
	int _x = InputHandler::Instance->curMouseX();
	int _y = InputHandler::Instance->curMouseY();
	return (glm::vec2(std::floor(_x/40.0f)*40, std::floor(_y/40.0f)*40));
}

void World::RenderMap(SDL_Renderer* r)
{
	SDL_RenderCopy(r, texture, NULL, NULL);
	SDL_Rect src = {0, 0, 40, 40};

	glm::vec2 m = getTileCoord();

	SDL_Rect dst = {m.x, m.y, 40, 40};
	SDL_RenderCopy(r, hoverTexture, &src, &dst);
}