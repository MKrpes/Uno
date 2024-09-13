#include "pch.h"
#include "Deck.h"


Deck::Deck(const Deck& other) : deck(other.deck) {}

Deck::Deck() {
	//generates cards that appear only once (number 0 cards)
	for(int i = 0; i < 4; i++) {
			deck.push_back(Card((CardColors)i, (CardTypes)0));
	}
	//generates cards that appear twice (numbers, skip, reverse and draw two)
	for (int n = 0; n < 2; n++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j < 13; j++) {
				deck.push_back(Card((CardColors)i, (CardTypes)j));
			}
		}
	}
	//generates wildcards (4 of color change and draw four each)
	for (int n = 0; n < 4; n++) {
		for (int i = 13; i < 15; i++) {
			deck.push_back(Card((CardColors)4, (CardTypes)i));
		}
	}
	Shuffle();
}
Deck::Deck(const std::vector<Card>& other) {
	deck = other;
	Shuffle();
}

Deck::~Deck() {
	deck.clear();
}

size_t Deck::Count() {
	return deck.size();
}

void Deck::Shuffle() {
	std::random_device rd;  
	std::mt19937 g(rd());
	std::shuffle(deck.begin(), deck.end(), g);
}

Card Deck::PopTopCard() {
	Card TopCard = deck.front();
	deck.erase(deck.begin());
	return TopCard;
}
std::vector<Card> Deck::GetStartingHand() {
	std::vector<Card> startingHand;
	for (uint32_t i = 0; i < 7; ++i) {
		startingHand.push_back(PopTopCard());
	}
	return startingHand;
}