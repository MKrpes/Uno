#pragma once
#include"Hand.h"
#include"Player.h"
#include<map>

class Bot : public Player
{
public:
	using Player::Player;
	Bot(const std::vector<Card> cards) : Player(cards) { }
	int ReturnHighestPriority(Card card, int drawsum=0);
	std::map<CardColors, UINT> ColorCount(bool countsWildcards=true);
	CardColors ChooseColorToChange();
};

