#pragma once

#include <iostream>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <glm.hpp>

#include "Mesh.h"

class World;

enum ENTITY_TYPE{ Tower, Ammo, Enemy };

class Entity
{
public:
	Entity();
	Entity(glm::vec2 position, glm::vec2 size);
	Entity(glm::vec2 pos, glm::vec2 size, std::map<std::string, std::string>* props);
	~Entity(void);
	virtual void Update(float time) = 0;

public:
	
	glm::vec2 pos;
	glm::vec2 size;
	glm::vec2 dir;
	glm::vec2 vel;

	Uint32 assetId;
	bool isDead;

	SDL_Texture* texture;

	int frames;
	SDL_Rect frameRect; // describes the frame size
	float frameLife;
	float currentFrameLife;
	int currentFrame;

	Uint32 id;
	Uint32 typeId;

	World* world; //reference to the world

protected:
	static Uint32 Ids;
	static Uint32 RequestId();
};