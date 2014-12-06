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

	//bool HasComponent(std::string family) const;
	//Component* GetComponent() const;


public:
	std::map<std::string, Component*> components;
	
	glm::vec3 pos;
	glm::vec3 size;
};