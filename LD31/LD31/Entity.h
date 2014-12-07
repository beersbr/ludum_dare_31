#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm.hpp>

#include "Component.h"

enum ENTITY_TYPE{ Tower, Ammo, Enemy };

class Entity
{
public:
	Entity(std::vector<Entity*>* entities);
	Entity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size);
	~Entity(void);
	virtual void Update(float time) = 0;

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
	glm::vec3 pos;
	glm::vec3 size;
	Uint32 assetId;
	bool isDead;
};