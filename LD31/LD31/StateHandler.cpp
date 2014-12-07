#include "StateHandler.h"


StateHandler::StateHandler(void)
{
	this->currentState = NULL;
}


StateHandler::~StateHandler(void)
{
}


bool UpdateGameState(SnowGameEvent* newState)
{
	//Do all logic to make sure we can update the game state,
	//return false if the state is illegal
	return true;
}
