#pragma once
#include<vector>
#include<algorithm>
#include"Card.h"

class Hand
{
public:
	std::vector<Card> hand;
	Hand(std::vector<Card> drawnCards);
	Hand() {};
	~Hand() {};
	void Sort();
	void RemoveCard(UINT i);
	void AddCard(const Card card);
	std::vector<UINT> CheckForAvailableCards(const Card card);
	std::vector<UINT> CheckForStackingCards(const Card card);
};

