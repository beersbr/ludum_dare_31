#pragma once
#include "entity.h"
class TowerEntity :
	public Entity
{
public:
	TowerEntity(std::vector<Entity*>* entities);
	TowerEntity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size);
	~TowerEntity();
	void setTarget(glm::vec3 targetLocation); //Do some magic to determine where you need to aim
	void isValidTarget(Entity* target); //Check if valid target is around
	void fire(); //create a bullet entity that will have a veclocity and target that this tower is currently set to
				 //Will also handle effects
	virtual void Update(float time);
private:
	//we already have a position and size, this will be a drawable entity (I guess they all are)
	//What attributes do towers have?
	Uint32 bulletType; //The tower will spawn bullet entities. Use the ID to get the correct info from the loader, or whoever
	Uint32 damage;
	Uint32 shotSpeed;
	glm::vec3 curDirection;

};

