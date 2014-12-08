#include "Entity.h"

#include "Component.h"


Entity::Entity(glm::vec2 position, glm::vec2 size) : pos(position), size(size)
{}

Entity::Entity(std::vector<Entity*>* entities) : entities(entities)
{
	this->pos = glm::vec2(0.0, 0.0);
	this->size = glm::vec2(0.0, 0.0);
}

Entity::Entity(std::vector<Entity*>* entities, glm::vec2 pos, glm::vec2 size) : entities(entities), pos(pos), size(size)
{
}


Entity::~Entity(void)
{
	//Whoa, we don't delete anything here yet..
}

