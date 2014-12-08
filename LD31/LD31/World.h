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
#include "InputHandler.h"



class World
{
public:
	World(Loader* loader);
	~World(void);
	bool createTowerEntity(std::string entityName);
	bool createEnemyEntity(std::string entityName);


	bool createTileAtPos(glm::vec2 const pos);
	//Entity* getTileAtPos(glm::vec2 const pos);
	Entity* getEntityAtPos(glm::vec2 const pos);
	bool isPointInEntity(glm::vec2 const pos, Entity* entity);
	bool createMap(SDL_Renderer* r);	
	void RenderMap(SDL_Renderer* r);

private:
	std::vector<Entity*> entities;
	Loader* loaderKing;
	std::vector<Entity*> tiles;

private:
	//int getPos(int x, int y);
	glm::vec2 getPos(int index);
	glm::vec2 getTileCoord(int x, int y);
	
	GLuint tilesVBO;

	SDL_Surface* surface;
	SDL_Texture* texture;

	SDL_Texture* hoverTexture;
};

