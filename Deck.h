#pragma once
#include <vector>
#include <algorithm> 
#include <random>    

#include "Card.h"

class Deck
	{

	

public:
	size_t Count();
	Deck();
	Card PopTopCard();
	std::vector<Card> deck;
	
	std::vector<Card> GetStartingHand();

	Deck(const Deck& other);
	Deck(const std::vector<Card>& other);
	~Deck();
	void Shuffle();
};

