#pragma once

#include <algorithm>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "TowerEntity.h"
#include "EnemyEntity.h"
#include "Loader.h"
//#include "LudumGame.h"

#include "TileEntity.h"
#include "Util.h"


class World
{
public:
	World(Loader* loader);
	~World(void);
	bool createTowerEntity(std::string entityName);
	bool createEnemyEntity(std::string entityName);


	bool createTileAtPos(glm::vec2 const pos);

	bool createMap(SDL_Renderer* r);	
	void RenderMap(SDL_Renderer* r);

private:
	std::vector<Entity*> entities;
	Loader* loaderKing;

	std::vector<Entity*> tiles;

private:
	//int getPos(int x, int y);
	glm::vec2 getPos(int index);

	GLuint tilesVBO;

	SDL_Surface* surface;
	SDL_Texture* texture;


};

