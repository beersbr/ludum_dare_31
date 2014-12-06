#pragma once

#include "Entity.h"

class World
{
public:
	World(void);
	~World(void);

public:
	std::vector<Entity*> entities;
};

