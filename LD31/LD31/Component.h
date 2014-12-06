#pragma once
#include <iostream>
#include <string>

#include "Util.h"

class Entity;

class Component
{
public:
	Component();
	virtual ~Component();

	template <typename T>
	static T* CreateComponent()
	{
		family = T::family
	}

	// TODO: accept a json string with the props
	//virtual void Create(jsonString) = 0;

public:
	Entity* GetOwner() const;
	void SetOwner(Entity* e);

public:
	std::string family;
	std::string name;

protected:
	Entity* owner;

};

