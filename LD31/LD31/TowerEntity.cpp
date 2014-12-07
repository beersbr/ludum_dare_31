#include "TowerEntity.h"


TowerEntity::TowerEntity(std::vector<Entity*>* entities, std::map<std::string, std::string>* props) : Entity(entities)
{
	this->bulletType = (*props)["ammoType"];
	this->health = atoi((*props)["health"].c_str());
	this->shotSpeed = atoi((*props)["shotSpeed"].c_str());
	this->damage = atoi((*props)["damage"].c_str());
}


TowerEntity::TowerEntity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size, std::map<std::string, std::string>* props) : Entity(entities, pos, size)
{
	this->bulletType = (*props)["ammoType"];
	this->health = atoi((*props)["health"].c_str());
	this->shotSpeed = atoi((*props)["shotSpeed"].c_str());
	this->damage = atoi((*props)["damage"].c_str());
}

TowerEntity::~TowerEntity(void)
{
}

void TowerEntity::Update(float time)
{

}