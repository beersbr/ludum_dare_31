#include "RenderComponent.h"


RenderComponent::RenderComponent(void)
{
}


RenderComponent::~RenderComponent(void)
{
}

void RenderComponent::Render(glm::mat4 P, glm::mat4 V)
{
	projection = P;
	view = V;
	Render();
}

void RenderComponent::Render()
{

}
