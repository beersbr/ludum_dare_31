#include "TowerEntity.h"


TowerEntity::TowerEntity(std::vector<Entity*>* entities) : Entity(entities)
{
}


TowerEntity::TowerEntity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size) : Entity(entities, pos, size)
{
}

TowerEntity::~TowerEntity(void)
{
}

void TowerEntity::Update(float time)
{

}