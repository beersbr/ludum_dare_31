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

bool World::CreateMap(SDL_Renderer* r)
{
	int mapWidth = 1200;
	int mapHeight = 800;

	surface = SDL_CreateRGBSurface(0, 1200, 800, 32, 0, 0, 0, 0);
	SDL_Rect surfaceRect = {0, 0, 1200, 800};

	SDL_Surface* tile = IMG_Load("assets/snow-tile.jpg");
	SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(r, tile);
	SDL_SetTextureBlendMode(tileTexture, SDL_BLENDMODE_BLEND);

	SDL_Rect tileSize = {0, 0, 40, 40};
	SDL_Rect dstRect = {0, 0, 40, 40};

	for(int i = 0; i < (mapWidth/40)*(mapHeight/40); ++i)
	{
		TILE t;
		t.baseTexture = tileTexture;

		int x = std::floor(i % (mapWidth/40));
		int y = i / (mapWidth/40);
		dstRect.x = x * 40;
		dstRect.y = y * 40;

		t.posPixel = glm::vec2(dstRect.x, dstRect.y);
		t.posIndex = glm::vec2(x, y);

		SDL_BlitSurface(tile, &tileSize, surface, &dstRect); 
		map.push_back(t);
	}

	// background texture
	texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	
	// create the hover texture
	SDL_Surface* s = SDL_CreateRGBSurface(0, 40, 40, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_Rect rect = {0, 0, 40, 40};
	SDL_FillRect(s, &rect, 0xFF000033);
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);
	hoverTexture = SDL_CreateTextureFromSurface(r, s);
	SDL_SetTextureBlendMode(hoverTexture, SDL_BLENDMODE_BLEND);
	

	InputHandler::Instance->listenLeftClick(World::worldMouseCallback);
	return false;
}


glm::vec2 World::getTileCoord(int x = -1, int y = -1)
{
	int _x = 0;
	int _y = 0;

	if(x < 0 && y < 0)
	{
		_x = x;
		_y = y;
	}
	else
	{
		_x = InputHandler::Instance->curMouseX();
		_y = InputHandler::Instance->curMouseY();
	}

	return (glm::vec2(std::floor(_x/40.0f)*40, std::floor(_y/40.0f)*40));
}

void World::RenderMap(SDL_Renderer* r, float dt)
{
	// ORDER:
	// tiles (background)
	// doodads 
	// towers
	// enemeis
	// hover (UI)
	// text
	
	// background (tiles) :)
	SDL_RenderCopy(r, texture, NULL, NULL);
	SDL_Rect src = {0, 0, 40, 40};

	// dooads
	std::vector<DOODAD> d;
	for(int i = 0; i < doodads.size(); ++i)
	{
		SDL_RenderCopy(r, doodads[i].texture, NULL, doodads[i].pos);
		if(doodads[i].update(dt))
			d.push_back(doodads[i]);
	}
	doodads = d;

	// hovers
	glm::vec2 m = getTileCoord();
	SDL_Rect dst = {m.x, m.y, 40, 40};
	SDL_RenderCopy(r, hoverTexture, &src, &dst);
}

void World::Update(float const dt)
{


	// do input handler stuff here... that means taking it out of the render function

	//InputHandler::mouseUp()

}