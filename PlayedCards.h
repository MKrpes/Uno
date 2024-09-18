#pragma once
#include<vector>
#include"Card.h"

class PlayedCards
{
	std::vector<Card> cardHistory;
public:
	PlayedCards(const Card card);
	~PlayedCards();

	std::vector<Card> resetDeck();

	void playerTurn(const Card card);
	const Card getLast();
};

