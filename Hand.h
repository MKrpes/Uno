#pragma once
#include<vector>
#include<algorithm>
#include"Card.h"

class Hand
{
public:
	std::vector<Card> hand;
	Hand(std::vector<Card> drawnCards);
	~Hand();
	void Sort();
	void RemoveCard(uint32_t i);
	void AddCard(const Card card);
	std::vector<uint32_t> CheckForAvailableCards(const Card card);
	std::vector<uint32_t> CheckForStackingCards(const Card card);
};

