#include "StateHandler.h"


StateHandler::StateHandler(InputHandler* inputKing) : inputKing(inputKing), currentState(NULL)
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

	return true;
}

