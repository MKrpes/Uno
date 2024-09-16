#pragma once
#include"Hand.h"

class Player
{
public:
	Hand* playerHand;
	Player(const std::vector<Card> cards);
	virtual ~Player();
	Card PlayerTurn(int i);
	bool hasDrawn = false;
};

