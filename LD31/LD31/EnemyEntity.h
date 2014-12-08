#pragma once

#include <iostream>

#include "World.h"
#include "Entity.h"


class EnemyEntity : 
	public Entity
{
public:
	EnemyEntity::EnemyEntity();
	EnemyEntity(std::map<std::string, std::string>* props); 
	EnemyEntity(glm::vec2 pos, glm::vec2 size, std::map<std::string, std::string>* props);
	~EnemyEntity();
	virtual void Update(float time);

private:
	Uint32 health;
	Uint32 moveSpeed;
	Uint32 atkSpeed;

	glm::vec2 dest;
};