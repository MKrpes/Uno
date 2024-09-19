#pragma once
#include "Scoreboard.h"
struct SavedGameSettings 
{
public:
	int playerCount=2;
	bool isFullscreen = false;
	types GameType = none;
	int winsNeeded = 5;
	int pointsNeeded = 500;
	
	~SavedGameSettings() {};
};

