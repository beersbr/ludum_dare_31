#pragma once
#include "entity.h"
#include <vector>

class AmmoEntity :
	public Entity
{
public:
	AmmoEntity(std::map<std::string, std::string>* props);
	AmmoEntity(glm::vec2 pos, glm::vec2 size, std::map<std::string, std::string>* props);
	~AmmoEntity(void);
	virtual void Update(float time); //When we update this, we will figure out where we are in our animation and apply damage to the targets.

private:
	Entity* towerOwner;
	std::vector<Entity*> targetList; //people we will apply damage to

};

