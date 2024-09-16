#include "pch.h"
#include "Player.h"

Player::Player(const std::vector<Card> cards) {
	playerHand = new Hand(cards);
}

Player::~Player()
{
}

Card Player::PlayerTurn(int i) {
	return playerHand->hand[i];
}
