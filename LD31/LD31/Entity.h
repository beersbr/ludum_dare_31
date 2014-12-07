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
	Entity(glm::vec3 position, glm::vec3 size);
	Entity(std::vector<Entity*>* entities);
	Entity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size);
	~Entity(void);
	virtual void Update(float time) = 0;

public:
	//std::map<std::string, Component*> components;
	std::vector<Entity*>* entities; //reference to the world
	glm::vec3 pos;
	glm::vec3 size;
	Uint32 assetId;
	bool isDead;

	SDL_Surface* surface;
	//Mesh mesh;
};