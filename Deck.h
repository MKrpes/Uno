#pragma once
#include <vector>
#include <algorithm> 
#include <random>    

#include "Card.h"

class Deck
	{

	

public:
	Deck();
	Card PopTopCard();
	Card PopTopNSCard();
	std::vector<Card> deck;
	
	std::vector<Card> GetStartingHand();

	Deck(const Deck& other);
	Deck(const std::vector<Card> other);
	~Deck();
	void Shuffle();
};

