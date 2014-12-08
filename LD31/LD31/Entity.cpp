#include "Entity.h"

#include "World.h"

Uint32 Entity::Ids = 0;

Uint32 Entity::RequestId()
{
	return ++Entity::Ids;
}

Entity::Entity()
{
	id = Entity::RequestId();
}

Entity::Entity(glm::vec2 position, glm::vec2 size) 
	 : pos(position), size(size)
{
	id = Entity::RequestId();
}

Entity::~Entity(void)
{
	//Whoa, we don't delete anything here yet..
}

