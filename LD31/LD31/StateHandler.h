#pragma once

#include <iostream>
#include <stack>
#include <vector>

#include "InputHandler.h"
#include "World.h"

//These should be possible states active while the game is running
#define SNOWGAMGE_RUN = 0x1; //Game is running
#define SNOWGAME_PAUSE = 0x1 << 1; //Game is paused
#define SNOWGAME_START_WAVE = 0x1 << 2; //Wave is started
#define SNOWGAME_END_WAVE = 0x1 << 3;	//End the wave
#define SNOWGAME_EDIT_DEF = 0x1 << 4;	//Tower defense is editable (we can place towers)	

class SnowGameEvent
{
public:
	unsigned int eventId;
	unsigned int stateFlags;
	std::vector<void*> params;
};

class StateHandler
{
public:
	StateHandler(InputHandler* inputKing, World* gameWorld);
	~StateHandler(void);
	bool UpdateGameState(float time);
	SnowGameEvent* GetSnowGameState();
private:
	InputHandler* inputKing;
	World* gameWorld;
	//void updateGameState();
	SnowGameEvent* currentState;
	std::stack<SnowGameEvent*> stateStack; //This might not be necessary
};

