#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm.hpp>

#include "Component.h"
#include "Mesh.h"

enum ENTITY_TYPE{ Tower, Ammo, Enemy, Tile };

class Entity
{
public:
	Entity(glm::vec2 position, glm::vec2 size);
	Entity(std::vector<Entity*>* entities);
	Entity(std::vector<Entity*>* entities, glm::vec2 pos, glm::vec2 size);
	~Entity(void);
	virtual void Update(float time) = 0;

public:
	//std::map<std::string, Component*> components;
	std::vector<Entity*>* entities; //reference to the world
	glm::vec2 pos;
	glm::vec2 size;
	Uint32 assetId;
	bool isDead;

	SDL_Surface* surface;
	//Mesh mesh;
};