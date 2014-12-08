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
	entities.push_back(new TowerEntity(towerProps));

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
	entities.push_back(new TowerEntity(enemyProps));

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

		int x = (int)std::floor(i % (mapWidth/40));
		int y = (int)(i / (mapWidth/40));
		dstRect.x = x * 40;
		dstRect.y = y * 40;

		t.posPixel = glm::vec2(dstRect.x, dstRect.y);
		t.posIndex = glm::vec2(x, y);

		SDL_BlitSurface(tile, &tileSize, surface, &dstRect); 

		if(x == 0 && y == 1){
			t.isStartTile = true;
			start = t;
		}

		if(x == 29 && y == 18){
			t.isEndTile = true;
			end = t;
		}

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
	
	InputHandler::Instance->ListenLeftClick(World::worldLeftMouseCallback);
	InputHandler::Instance->ListenRightClick(World::worldRightMouseCallback);

	EnemyEntity* e = new EnemyEntity(); 
	e->texture = ImageController::Instance()->GetTexture("snowman1");
	e->frames = 4;
	SDL_Rect frameSize = {0, 0, 80, 80};
	e->frameRect = frameSize;
	e->size = glm::vec2(40.0f, 40.0f);
	e->pos = glm::vec2(580, 380);


	entities.push_back(e);

	return false;
}


glm::vec2 World::getTileCoord(int x = -1, int y = -1)
{
	int _x = 0;
	int _y = 0;

	if(x >= 0 && y >= 0)
	{
		_x = x;
		_y = y;
	}
	else 
	{
		return glm::vec2(-1, -1);
	}

	return (glm::vec2(std::floor(_x/40.0f)*40, std::floor(_y/40.0f)*40));
}

glm::vec2 World::GetTileCoordByIndex(int idx)
{
	// MORE MAGIC NUMBERS
	// 30 is the horizontal tile number
	// 20 is the vertical tile number
	return glm::vec2(idx%30, std::floor(idx/30));
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

	for(int i = 0; i < entities.size(); ++i)
	{
		SDL_Rect dst = {entities[i]->pos.x, entities[i]->pos.y, entities[i]->size.x, entities[i]->size.y };
		SDL_RenderCopy(r, entities[i]->texture, &entities[i]->frameRect, &dst);
	}

	// hovers
	glm::vec2 m = getTileCoord(InputHandler::Instance->GetMousePos().x, InputHandler::Instance->GetMousePos().y);
	SDL_Rect dst = {(int)m.x, (int)m.y, 40, 40};
	SDL_RenderCopy(r, hoverTexture, &src, &dst);
}

void World::Update(float const dt)
{
	// get mouse up and do something

	// do input handler stuff here... that means taking it out of the render function
	// clear mouse states
	//EvalPath();

	for(int i = 0; i < entities.size(); ++i)
	{
		entities[i]->Update(dt);
	}

}

bool World::isPointInEntity(glm::vec2 const pos, Entity* entity)
{
	double tmpX = entity->pos.x + entity->size.x;
	//check if we're in the right X direction
	if((!pos.x >= entity->pos.x) && !(pos.x <= tmpX))
	{
		return false;
	}

	double tmpY = entity->pos.y + entity->size.y;

	if((!pos.y >= entity->pos.y) && !(pos.y <= tmpY))
	{
		return false;
	}

	return true;
}

Entity* World::getEntityAtPos(glm::vec2 const pos)
{
	for(std::vector<Entity*>::iterator iter = this->entities.begin(); iter != this->entities.end(); iter++)
	{
		if(isPointInEntity(pos, (*iter)))
		{
			return (*iter);
		}
	}

	return NULL;
}

void World::SetMouseDown(int x, int y)
{
	mouseUp = glm::vec2(x, y);
}

void World::SetMouseUp(int x, int y)
{
	mouseDown = glm::vec2(x, y);
}

glm::vec2 World::GetMouseDown()
{
	glm::vec2 p = glm::vec2((float)mouseDown.x, (float)mouseDown.y);
	mouseDown = glm::vec2(-1, -1);
	return p;
}

glm::vec2 World::GetMouseUp()
{
	glm::vec2 p = glm::vec2((float)mouseUp.x, (float)mouseUp.y);
	mouseUp = glm::vec2(-1, -1);
	return p;
}

void World::EvalPath()
{
	// A* search
	std::list<PATHNODE> pathnodes; // a list of all the nodes to keep the data in scope;

	std::list<PATHNODE> openList;
	std::list<PATHNODE> closedList;

	PATHNODE start = { nullptr, this->start, 0, 0, Dist( this->start.posIndex, this->end.posIndex) };
	pathnodes.push_back(start);
	openList.push_back(start);

	while(openList.size() > 0)
	{
		PATHNODE N = openList.front();
		openList.pop_front();

		// get children to N
		int curIdx = GetIndexByCoord(N.tile.posIndex);
		std::vector<PATHNODE> children;

		int pG = 0; // parents G value
		if(N.parent)
			pG = N.G;

		TILE* t;

		// NORTH 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x, N.tile.posIndex.y-1))) /* width in tiles */
		{
			TILE m = *t; // map[curIdx-30];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.0 + pG;
			PATHNODE t = {&N, map[curIdx-30], g, h, h+g};
			children.push_back(t);
		}

		// NORTH EAST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x+1, N.tile.posIndex.y-1))) /* width in tiles */
		{
			TILE m = *t; //map[curIdx-30+1];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.2 + pG;
			PATHNODE t = {&N, map[curIdx-30+1], g, h, h+g};
			children.push_back(t);
		}

		// EAST
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x+1, N.tile.posIndex.y))) /* width in tiles */
		{
			TILE m = *t; // map[curIdx+1];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.0 + pG;
			PATHNODE t = {&N, map[curIdx+1], g, h, h+g};
			children.push_back(t);
		}

		// SOUTH EAST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x+1, N.tile.posIndex.y+1))) /* width in tiles */
		{
			TILE m = *t; // map[curIdx + 30 + 1];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.2 + pG;
			PATHNODE t = {&N, map[curIdx + 30 + 1], g, h, h+g};
			children.push_back(t);
		}

		// SOUTH
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x, N.tile.posIndex.y+1))) /* width in tiles */
		{
			TILE m = *t; //map[curIdx+30];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.0 + pG;
			PATHNODE t = {&N, map[curIdx+30], g, h, h+g};
			children.push_back(t);
		}

		// SOUTH WEST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x-1, N.tile.posIndex.y+1))) /* width in tiles */
		{
			TILE m = *t; //map[curIdx + 30 -1];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.2 + pG;
			PATHNODE t = {&N, map[curIdx + 30 -1], g, h, h+g};
			children.push_back(t);
		}

		// WEST
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x-1, N.tile.posIndex.y))) /* width in tiles */
		{
			TILE m = *t; // map[curIdx - 1];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.0 + pG;
			PATHNODE t = {&N, map[curIdx - 1], g, h, h+g};
			children.push_back(t);
		}

		// NORTH WEST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x-1, N.tile.posIndex.y-1))) /* width in tiles */
		{
			TILE m = *t; //map[curIdx - 30 - 1];
			int h = Dist(m.posIndex, end.posIndex);
			int g = 1.2 + pG;
			PATHNODE t = {&N, map[curIdx - 30 - 1], g, h, h+g};
			children.push_back(t);
		}


		for(int i = 0; i < children.size(); ++i)
		{
			pathnodes.push_back(children[i]);
			// if this tile is the end tile we are done, just need to save the path
			if(children[i].H == 0.0)
			{
				fprintf(stdout, "FOUND END TILE!\n");
			}

			if(children[i].tile.isEndTile)
			{
				PATHNODE* p = &children[i];
				safePath.push_front(map[GetIndexByCoord(p->tile.posIndex)]);
				while(p = p->parent)
				{
					safePath.push_front(map[GetIndexByCoord(p->tile.posIndex)]);
				}
				fprintf(stdout, "Found a path!\n");
				return;
			}

			bool dontAdd = false;
			// if this tile has already been added to the open list AND
			// there is it has a better F value we skip it
			for(auto it = openList.begin(); it != openList.end(); ++it)
			{
				if((*it).tile.posIndex == children[i].tile.posIndex
					&& (*it).F <= children[i].F)
				{
					dontAdd = true;
				}
			}

			// do the same for the closed list
			for(auto it = closedList.begin(); it != closedList.end(); ++it)
			{
				if((*it).tile.posIndex == children[i].tile.posIndex
					&& (*it).F <= children[i].F)
				{
					dontAdd = true;
				}
			}

			if(!dontAdd)
				openList.push_back(children[i]);
		}
		
		openList.sort(PATHNODE_sort);

		closedList.push_back(N);
	}
}


int World::GetIndexByCoord(glm::vec2 c)
{
	return (c.y * ( 30 ) + c.x);
}

float World::Dist(glm::vec2 a, glm::vec2 b)
{
	return std::sqrtf(((a.x-b.x)*(a.x-b.x)) + ((a.y-b.y)*(a.y-b.y)));
}

TILE* World::GetTileAtCoord(glm::vec2 coord)
{
	if(coord.x < 0 || coord.y < 0 || coord.x >= 30 || coord.y >= 20)
		return nullptr;

	return &map[GetIndexByCoord(coord)];
}

bool PATHNODE_sort(const PATHNODE& first, const PATHNODE& second)
{
	return (first.F < second.F);
}