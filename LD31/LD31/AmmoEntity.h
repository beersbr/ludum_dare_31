#pragma once
#include "entity.h"
#include <vector>

class AmmoEntity :
	public Entity
{
public:
	AmmoEntity(std::vector<Entity*>* entities);
	AmmoEntity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size);
	~AmmoEntity(void);
	virtual void Update(float time); //When we update this, we will figure out where we are in our animation and apply damage to the targets.

private:
	Entity* towerOwner;
	std::vector<Entity*> targetList; //people we will apply damage to

};

