#include "Component.h"
#include "Entity.h"

Component::Component()
{

}

Entity* Component::GetOwner() const
{
	return owner;
}

void Component::SetOwner(Entity* e)
{
	owner = e;
}

Component::~Component()
{
	safe_delete<Entity>(owner);
}