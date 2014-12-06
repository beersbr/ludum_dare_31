#include "Entity.h"

#include "Component.h"

Entity::Entity(void)
{
	components.clear();
	Entity::entities.push_back(this);
}


Entity::~Entity(void)
{

}

bool Entity::HasComponent(std::string const family) const
{
	auto it = components.find(family);
	return (it != components.end());
}

Component* Entity::GetComponent(std::string const family)
{
	return (components[family]);
}
