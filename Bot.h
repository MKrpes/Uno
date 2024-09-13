#pragma once
#include"Hand.h"
#include"Player.h"

class Bot : public Player
{
public:
	Hand* playerHand;
	using Player::Player;
	//Bot(const std::vector<Card> cards) : Player(cards){}
	//uint32_t ReturnHighestPriority();

};

