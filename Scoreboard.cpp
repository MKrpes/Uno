#include "pch.h"
#include "Scoreboard.h"

Scoreboard::Scoreboard(const int playerCount,const types gameType,const int rPoints){
	requiredPoints = rPoints;
	type = gameType;
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

int Scoreboard::GetPlayerPoints(const int i)
{
	return points[i];
}

Scoreboard::~Scoreboard()
{
	points.clear();
}

void Scoreboard::resetScoreboard()
{
	for (int i = 0; i < points.size(); ++i) {
		points[i] = 0;
	}
}

bool Scoreboard::WritePoints(const int player,const int pointsSum)
{
	switch (type) {
	case 0:
		return true;
	case 1: {
		points[player] += 1;
		return points[player] > requiredPoints;
	}
	case 2: {
		points[player] += pointsSum;
		return points[player] > requiredPoints;
	}
	}
}
