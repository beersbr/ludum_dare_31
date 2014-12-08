#include "AmmoEntity.h"


AmmoEntity::AmmoEntity(std::vector<Entity*>* entities) : Entity(entities)
{
}

AmmoEntity::AmmoEntity(std::vector<Entity*>* entities, glm::vec2 pos, glm::vec2 size) : Entity(entities, pos, size)
{
}

AmmoEntity::~AmmoEntity(void)
{
}

void AmmoEntity::Update(float time)
{
	//Do some updating based on what time it is
	return;
}
