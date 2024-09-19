#pragma once
#include"Hand.h"
#include<map>


class Player
{
public:
	Hand playerHand;
	Player(const std::vector<Card>& cards);
	Player() {};
	~Player() {};
	void newGame(const std::vector<Card>& cards);
	Card PlayerTurn(int i);
	bool hasDrawn = false;

	int ReturnHighestPriority(Card card, int drawsum = 0);
	std::map<CardColors, UINT> ColorCount(bool countsWildcards = true);
	CardColors ChooseColorToChange();
};

