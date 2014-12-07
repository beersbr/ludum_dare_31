#pragma once

#include "TowerEntity.h"
#include "EnemyEntity.h"
#include "Loader.h"
#include "LudumGame.h"

class World
{
public:
	World(Loader* loader);
	~World(void);
	bool createTowerEntity(std::string entityName);
	bool createEnemyEntity(std::string entityName);

private:
	std::vector<Entity*> entities;
	Loader* loaderKing;
};

