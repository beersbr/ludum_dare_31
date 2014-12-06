#pragma once
#include <iostream>
#include <string>

class Entity;

class Component
{
public:
	Component();
	virtual ~Component();

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

