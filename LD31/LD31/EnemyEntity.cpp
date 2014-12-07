#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::vector<Entity*>* entities) : Entity(entities)
{
}

EnemyEntity::EnemyEntity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size): Entity(entities, pos, size)
{
}

void EnemyEntity::Update(float time)
{
	return;
}