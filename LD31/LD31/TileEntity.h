#pragma once
#include "entity.h"

// container for tiles, the World will be the controller

class TileEntity :
	public Entity
{
public:
	TileEntity(glm::vec2 const position, glm::vec2 const size);
	~TileEntity(void);

	 virtual void Update(float time);
	 void Render();

public:
	bool isSelected;
};

