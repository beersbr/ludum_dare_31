#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Component.h"
#include "Mesh.h"

class RenderComponent :
	public Component
{
public:
	RenderComponent(void);
	virtual ~RenderComponent(void);

	void Render(glm::mat4 P, glm::mat4 V);
	void Render();

public:
	glm::mat4 projection;
	glm::mat4 view;

	Mesh mesh;

};

