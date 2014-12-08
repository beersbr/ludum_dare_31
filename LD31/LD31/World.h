#pragma once

#include <algorithm>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "TowerEntity.h"
#include "EnemyEntity.h"
#include "Loader.h"
#include "TileEntity.h"
#include "Util.h"
#include "InputHandler.h"

typedef struct DOODAD
{
	static DOODAD create(int const x, int const y, int const w, int const h, SDL_Texture* tex)
	{
		DOODAD d;
		d.pos = new SDL_Rect();
		d.pos->x = x;
		d.pos->y = y;
		d.pos->w = w;
		d.pos->h = h;

		d.texture = tex;
		d.isDead = false;
		d.liveFor = 10; 
		d.life = 0;
	}

	bool update(float dt)
	{
		life += dt;
		if(life >= liveFor)
		{
			isDead = true;
		}

		return isDead;
	}

	~DOODAD()
	{
		safe_delete<SDL_Rect>(pos);
		pos = nullptr;

	}

	SDL_Texture* texture;
	bool isDead;
	SDL_Rect* pos;

	float life; // they live for 10 seconds
	float liveFor;
};

typedef struct TILE
{
	TILE()
	{
		isSelected = false;
		isHovered = false;
		Tower = nullptr;
	}

	bool hasTower()
	{
		return (Tower == nullptr);
	}

	Entity* Tower;

	bool isSelected;
	bool isHovered;

	SDL_Texture* baseTexture;		// used for the map creation

	glm::vec2 posPixel;
	glm::vec2 posIndex;
};

class World
{
public:
	World(Loader* loader);
	~World(void);
	bool createTowerEntity(std::string entityName);
	bool createEnemyEntity(std::string entityName);


	bool createTileAtPos(glm::vec2 const pos);

	bool createMap(SDL_Renderer* r);	
	void RenderMap(SDL_Renderer* r, float dt);

private:
	std::vector<Entity*> entities;
	Loader* loaderKing;

private:
	glm::vec2 getPos(int index);
	glm::vec2 getTileCoord(int x, int y);

	std::vector<DOODAD> doodads;
	std::vector<TILE> map;

	SDL_Surface* surface;
	SDL_Texture* texture;

	SDL_Texture* hoverTexture;
};

