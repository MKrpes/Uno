#include "pch.h"
#include "Scoreboard.h"

Scoreboard::Scoreboard(int playerCount, types type, int rPoints){
	requiredPoints = rPoints;
	for (int i = 0; i < playerCount; ++i) {
		points[i] = 0;
	}
}

std::map<int, int> Scoreboard::GetPoints() const
{
	return points;
}

int Scoreboard::GetType() const
{
	return type;
}

int Scoreboard::GetReqPoints() const
{
	return requiredPoints;
}
