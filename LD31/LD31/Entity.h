#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm.hpp>

#include "Component.h"
#include "World.h"

class Entity
{
public:
	Entity(World* world); //In case the entity must be aware of the world
	Entity(World* world, glm::vec3& pos, glm::vec3& size);
	~Entity(void);

	//bool HasComponent(std::string const family) const;
	/*
	template <typename T>
	T* TGetComponent()
	{
		return 
	}
	*/
	//Component* GetComponent(std::string const family);


public:
	//std::map<std::string, Component*> components;
	std::vector<Entity*>* entities; //reference to the world
	World* myWorld;
	glm::vec3 pos;
	glm::vec3 size;
	Uint32 surfaceID;
	bool isDead;
};