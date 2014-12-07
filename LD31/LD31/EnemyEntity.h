#include "World.h"
#include "Entity.h"
#include <iostream>

class EnemyEntity : 
	public Entity
{
public:
	EnemyEntity(std::vector<Entity*>* entities);
	EnemyEntity(std::vector<Entity*>* entities, glm::vec3& pos, glm::vec3& size);
	~EnemyEntity();
	virtual void Update(float time);
private:
	Uint32 health;
	Uint32 moveSpeed;
	Uint32 atkSpeed;
};