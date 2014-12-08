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
	frameLife = 1/8.0f; // 1/8th of a second for each frame
	currentFrameLife = 0.0f;
	currentFrame = 0;
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

