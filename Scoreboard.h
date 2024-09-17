#pragma once

#include<map>

enum types
{
	wins,points
};

class Scoreboard
{
	types type;
	int requiredPoints;
	std::map<int, int> points;
public:
	Scoreboard(int playerCount, types type, int rPoints);
	std::map<int, int> GetPoints() const;
	int GetType() const;
	int GetReqPoints() const;
};

