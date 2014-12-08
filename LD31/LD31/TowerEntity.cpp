#include "TowerEntity.h"


TowerEntity::TowerEntity(glm::vec2 pos, glm::vec2 size, std::map<std::string, std::string>* props) 
	: Entity(pos, size)
{
	this->bulletType = (*props)["ammoType"];
	this->health = atoi((*props)["health"].c_str());
	this->shotSpeed = atoi((*props)["shotSpeed"].c_str());
	this->damage = atoi((*props)["damage"].c_str());
}


TowerEntity::TowerEntity(std::map<std::string, std::string>* props)
	: Entity()
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