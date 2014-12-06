#pragma once

#include <vector>
#include <glm.hpp>

class Component;

class Entity
{
public:
	Entity(void);
	~Entity(void);

public:
	std::vector<Component*> components;
	glm::vec3 pos;
	glm::vec3 size;
};

