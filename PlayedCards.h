#pragma once
#include<vector>
#include"Card.h"

class PlayedCards
{
	std::vector<Card> cardHistory;
public:
	PlayedCards(const Card card);
	~PlayedCards();

	void playerTurn(const Card card);
	const Card getLast();
};

