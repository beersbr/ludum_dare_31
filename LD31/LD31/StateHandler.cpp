#include "StateHandler.h"


StateHandler::StateHandler(InputHandler* inputKing, World* gameWorld) : inputKing(inputKing), currentState(NULL), gameWorld(gameWorld)
{
}


StateHandler::~StateHandler(void)
{
}


bool StateHandler::UpdateGameState(float time)
{
	//Do all logic to make sure we can update the game state,
	//return false if the state is illegal
	//Assume this is being called every Game Update call
	//If these are available, manipulate state based on the current state
	//first check if the mouse is clicked
	auto mouseButton = inputKing->GetMouseButton();
	if(mouseButton)
	{
		//mosue click
		if(mouseButton == SDL_BUTTON_LEFT)
		{
			//left mouse click, what do we do with that?
			
			//We usually always care about a left click
			Entity* clickedEntity =  gameWorld->getEntityAtPos(inputKing->GetMousePos());
			if(clickedEntity)
			{
				//We clicked on an entity, deal with this given the state;	
			}
		}
			
	}


	return true;
}

