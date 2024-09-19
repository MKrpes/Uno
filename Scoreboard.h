#pragma once

#include<map>

enum types
{
	none,wins,points
};

class Scoreboard
{
	friend class Game;
	types type;
	int requiredPoints;
	std::map<int, int> points;
	void resetScoreboard();
	bool WritePoints(const int player, const int pointsSum = 1);

public:
	Scoreboard() {};
	Scoreboard(int playerCount,types type,int rPoints=5);
	std::map<int, int> GetPoints() const;
	int GetType() const;
	int GetReqPoints() const;
	int GetPlayerPoints(const int i);
	~Scoreboard() {};
};

