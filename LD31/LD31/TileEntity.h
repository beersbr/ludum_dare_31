#pragma once
#include "entity.h"

// container for tiles, the World will be the controller

class TileEntity :
	public Entity
{
public:
	TileEntity(glm::vec3 const position, glm::vec3 const size);
	~TileEntity(void);

	 virtual void Update(float time);
	 void Render();

public:
	bool isSelected;
};

