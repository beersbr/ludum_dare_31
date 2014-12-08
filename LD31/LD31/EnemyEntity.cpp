#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::map<std::string, std::string>* props) 
	: Entity()
{
	this->health = atoi((*props)["health"].c_str());
	this->moveSpeed = atoi((*props)["moveSpeed"].c_str());
	this->atkSpeed = atoi((*props)["atkSpeed"].c_str());
}

EnemyEntity::EnemyEntity(glm::vec2 pos, glm::vec2 size, std::map<std::string, std::string>* props)
	: Entity(pos, size)
{
	this->health = atoi((*props)["health"].c_str());
	this->moveSpeed = atoi((*props)["moveSpeed"].c_str());
	this->atkSpeed = atoi((*props)["atkSpeed"].c_str());
}

void EnemyEntity::Update(float time)
{
	return;
}