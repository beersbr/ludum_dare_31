#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm.hpp>

#include "Component.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	bool HasComponent(std::string const family) const;

	template <typename T>
	T* TGetComponent()
	{
		return 
	}

	Component* GetComponent(std::string const family);


public:
	std::map<std::string, Component*> components;
	std::vector<Entity*> entities;

	glm::vec3 pos;
	glm::vec3 size;
};