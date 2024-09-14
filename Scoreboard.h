#pragma once

#include<map>

class Scoreboard
{
	int requiredPoints;
	std::map<int, int> points;
public:
	Scoreboard(int playerCount, int type, int points);

};

