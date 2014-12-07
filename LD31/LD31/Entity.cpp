#include "Entity.h"

#include "Component.h"


Entity::Entity(glm::vec3 position, glm::vec3 size)
{
	this->pos = position;
	this->size = size;
}

Entity::Entity(std::vector<Entity*>* entities)
{
	//this->myWorld = world;
	this->entities = (entities);
	this->pos = glm::vec3(0.0, 0.0, 0.0);
	this->size = glm::vec3(0.0, 0.0, 0.0);
	//components.clear();
	//Entity::entities.push_back(this);
}

Entity::Entity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size)
{
	this->entities = entities;
	this->pos = pos;
	this->size = size;
}


Entity::~Entity(void)
{
	//Whoa, we don't delete anything here yet..
}

