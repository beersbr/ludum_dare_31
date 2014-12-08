#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::vector<Entity*>* entities, std::map<std::string, std::string>* props) : Entity(entities)
{
	this->health = atoi((*props)["health"].c_str());
	this->moveSpeed = atoi((*props)["moveSpeed"].c_str());
	this->atkSpeed = atoi((*props)["atkSpeed"].c_str());
}

EnemyEntity::EnemyEntity(std::vector<Entity*>* entities, std::map<std::string, std::string>* props, glm::vec2 pos, glm::vec2 size): Entity(entities, pos, size)
{
	this->health = atoi((*props)["health"].c_str());
	this->moveSpeed = atoi((*props)["moveSpeed"].c_str());
	this->atkSpeed = atoi((*props)["atkSpeed"].c_str());
}

void EnemyEntity::Update(float time)
{
	return;
}