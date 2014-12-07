#include "Entity.h"

#include "Component.h"

Entity::Entity(World* world)
{
	this->myWorld = world;
	this->entities = world->entities;
	this->pos = glm::vec3(0.0, 0.0, 0.0);
	this->size = glm::vec3(0.0, 0.0, 0.0);
	//components.clear();
	//Entity::entities.push_back(this);
}

Entity::Entity(World* world, glm::vec3& pos, glm::vec3& size)
{
	//I DONT KNOW MY WORLD!?
	this->myWorld = NULL;
	this->entities = entities;
	this->pos = pos;
	this->size = size;
}


Entity::~Entity(void)
{
	//Whoa, we don't delete anything here yet..
}

