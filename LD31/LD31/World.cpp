#include "World.h"

static int CreatePathThread(void *ptr)
{
	World* world = (World*)ptr;
	(world->EvalPath());
	return 0;
}

World::World(Loader* loader)
{
	this->loaderKing = loader;
	curTime = 0.0f;
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
	SDL_Surface* h = SDL_CreateRGBSurface(0, 40, 40, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_Rect hrect = {0, 0, 40, 40};
	SDL_FillRect(h, &hrect, 0xFF000033);
	SDL_SetSurfaceBlendMode(h, SDL_BLENDMODE_BLEND);
	hoverTexture = SDL_CreateTextureFromSurface(r, h);
	SDL_SetTextureBlendMode(hoverTexture, SDL_BLENDMODE_BLEND);

	// start tile
	SDL_Surface* s = SDL_CreateRGBSurface(0, 40, 40, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_Rect srect = {0, 0, 40, 40};
	SDL_FillRect(s, &srect, 0x00FF0033);
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);
	startTileTexture = SDL_CreateTextureFromSurface(r, s);
	SDL_SetTextureBlendMode(startTileTexture, SDL_BLENDMODE_BLEND);

	// end tile
	SDL_Surface* e = SDL_CreateRGBSurface(0, 40, 40, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_Rect erect = {0, 0, 40, 40};
	SDL_FillRect(e, &erect, 0x0000FF33);
	SDL_SetSurfaceBlendMode(e, SDL_BLENDMODE_BLEND);
	endTileTexture = SDL_CreateTextureFromSurface(r, e);
	SDL_SetTextureBlendMode(endTileTexture, SDL_BLENDMODE_BLEND);
	
	EvalPath();

	// test enemey
	EnemyEntity* enemy = new EnemyEntity(); 
	enemy->texture = ImageController::Instance()->GetTexture("snowman1");
	enemy->frames = 4;
	SDL_Rect frameSize = {0, 0, 80, 80};
	enemy->frameRect = frameSize;
	enemy->size = glm::vec2(40.0f, 40.0f);
	enemy->pos = glm::vec2(580, 380);
	enemy->world = this;

	entities.push_back(enemy);

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

	return (glm::vec2(std::floor(_x/40.0f), std::floor(_y/40.0f)));
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

	// enemies
	for(int i = 0; i < entities.size(); ++i)
	{
		// should probably be responsible for drawing itself... oh well. NO TIME!
		SDL_Rect dst = {entities[i]->pos.x, entities[i]->pos.y, entities[i]->size.x, entities[i]->size.y };
		SDL_RenderCopyEx(
			r, 
			entities[i]->texture, 
			&entities[i]->frameRect, 
			&dst, 
			std::atan2(entities[i]->vel.x, entities[i]->vel.y) * -(180.0/3.14159), 
			NULL, SDL_FLIP_NONE);




	}

	// hovers
	glm::vec2 s = getTileCoord(start.posPixel.x, start.posPixel.y);
	SDL_Rect sst = {(int)s.x*40, (int)s.y*40, 40, 40};
	SDL_RenderCopy(r, startTileTexture, &src, &sst);

	glm::vec2 e = getTileCoord(end.posPixel.x, end.posPixel.y);
	SDL_Rect est = {(int)e.x*40, (int)e.y*40, 40, 40};
	SDL_RenderCopy(r, endTileTexture, &src, &est);

	glm::vec2 m = getTileCoord(InputHandler::Instance()->GetMousePos().x, InputHandler::Instance()->GetMousePos().y);
	SDL_Rect dst = {(int)m.x*40, (int)m.y*40, 40, 40};
	SDL_RenderCopy(r, hoverTexture, &src, &dst);
}

void World::Update(float const dt)
{
	// get mouse up and do something

	// do input handler stuff here... that means taking it out of the render function
	// clear mouse states
	if((curTime += dt) > 5){
		// find a new path every 5 seconds OR on map change
		//SDL_CreateThread(CreatePathThread, "createPath", (void*)this);
		curTime = 0.0;
	}

	if(InputHandler::Instance()->GetMouseClicks().size() > 0)
	{
		/*EnemyEntity* enemy = new EnemyEntity(); 
		enemy->texture = ImageController::Instance()->GetTexture("snowman1");
		enemy->frames = 4;
		SDL_Rect frameSize = {0, 0, 80, 80};
		enemy->frameRect = frameSize;
		enemy->size = glm::vec2(40.0f, 40.0f);
		enemy->pos = glm::vec2(580, 380);
		enemy->world = this;

		entities.push_back(enemy);*/

		glm::vec2 tilePixelCoord = getTileCoord(InputHandler::Instance()->GetMousePos().x, InputHandler::Instance()->GetMousePos().y);
		tilePixelCoord = glm::vec2(tilePixelCoord.x * 40, tilePixelCoord.y * 40);

		TowerEntity* tower = new TowerEntity();
		tower->texture = ImageController::Instance()->GetTexture("projectile-tower");
		tower->frames = 1;
		SDL_Rect frameSize = { 0, 0, 120, 120 };
		tower->frameRect = frameSize;
		tower->size = glm::vec2(40, 40);
		tower->pos =  tilePixelCoord;
		tower->world = this;

		int idx = GetIndexByCoord(getTileCoord(tilePixelCoord.x, tilePixelCoord.y));

		// TODO:  check if it is in bounds probably...
		if(!map[idx].hasTower())
		{
			map[idx].Tower = tower;
			entities.push_back(tower);
			//EvalPath();
			for(auto i = safePath.begin(); i != safePath.end(); ++i)
			{
				if((*i).posPixel == tower->pos)
				{
					SDL_CreateThread(CreatePathThread, "createPath", (void*)this);
					break;
				}
			}
			
		}
	}


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


std::list<TILE> World::EvalPath()
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
			if(t->hasTower() == false)
			{
				TILE m = *t; // map[curIdx-30];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.0 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx-30], g, h, h+g};
				children.push_back(t);
			}
		}

		// NORTH EAST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x+1, N.tile.posIndex.y-1))) 
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; //map[curIdx-30+1];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.2 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx-30+1], g, h, h+g};
				children.push_back(t);
			}
		}

		// EAST
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x+1, N.tile.posIndex.y))) 
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; // map[curIdx+1];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.0 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx+1], g, h, h+g};
				children.push_back(t);
			}
		}

		// SOUTH EAST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x+1, N.tile.posIndex.y+1))) 
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; // map[curIdx + 30 + 1];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.2 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx + 30 + 1], g, h, h+g};
				children.push_back(t);
			}
		}

		// SOUTH
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x, N.tile.posIndex.y+1))) 
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; //map[curIdx+30];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.0 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx+30], g, h, h+g};
				children.push_back(t);
			}
		}

		// SOUTH WEST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x-1, N.tile.posIndex.y+1))) 
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; //map[curIdx + 30 -1];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.2 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx + 30 -1], g, h, h+g};
				children.push_back(t);
			}
		}

		// WEST
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x-1, N.tile.posIndex.y))) 
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; // map[curIdx - 1];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.0 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = {p, map[curIdx - 1], g, h, h+g};
				children.push_back(t);
			}
		}

		// NORTH WEST 
		if(t = GetTileAtCoord(glm::vec2(N.tile.posIndex.x-1, N.tile.posIndex.y-1))) /* width in tiles */
		{
			if(t->hasTower() == false)
			{
				TILE m = *t; //map[curIdx - 30 - 1];
				int h = Dist(m.posIndex, end.posIndex);
				int g = 1.2 + pG;
				PATHNODE* p = (new PATHNODE(N));
				PATHNODE t = { p, map[curIdx - 30 - 1], g, h, h+g};
				children.push_back(t);
			}
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
				//std::list<TILE> safePath;

				PATHNODE* p = &children[i];
				safePath.push_front(map[GetIndexByCoord(p->tile.posIndex)]);
				while(p = p->parent)
				{
					safePath.push_front(map[GetIndexByCoord(p->tile.posIndex)]);
				}
				fprintf(stdout, "Found a path!\n");
				return safePath;
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
					break;
				}
			}

			// do the same for the closed list
			for(auto it = closedList.begin(); it != closedList.end(); ++it)
			{
				if((*it).tile.posIndex == children[i].tile.posIndex
					&& (*it).F <= children[i].F)
				{
					dontAdd = true;
					break;
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

