#include "pch.h"
#include "Deck.h"


Deck::Deck(const Deck& other) : deck(other.deck) {
	for (Card card : deck) {
		if (card.getType() == DrawFour || card.getType() == ColorChange) {
			card.Color = Wildcard;
		}
	}
	Shuffle(); 
}

Deck::Deck() {
	//generates cards that appear only once (number 0 cards)
	for(int i = Red; i < Wildcard; ++i) {
			deck.push_back(Card((CardColors)i, ZERO));
	}
	//generates cards that appear twice (numbers, skip, reverse and draw two)
	for (int n = 0; n < 2; ++n) {
		for (int i = Red; i < Wildcard; ++i) {
			for (int j = ONE; j < ColorChange; ++j) {
				deck.push_back(Card((CardColors)i, (CardTypes)j));
			}
		}
	}
	//generates wildcards (4 of color change and draw four each)
	for (int n = 0; n < 4; ++n) {
		for (int i = ColorChange; i <=DrawFour ; ++i) {
			deck.push_back(Card(Wildcard, (CardTypes)i));
		}
	}
	Shuffle();
}
Deck::Deck(const std::vector<Card> other) {
	deck = other;
	for (Card card : deck) {
		if (card.getType() == DrawFour || card.getType() == ColorChange) {
			card.Color = Wildcard;
		}
	}
	Shuffle();
}

Deck::~Deck() {
	deck.clear();
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
Card Deck::PopTopNSCard()
{
	for (UINT i = 0; i < deck.size(); ++i) {
		if (deck[i].Type >= Skip) continue;
		else {
			Card card = deck[i];
			deck.erase(deck.begin() + i);
			return card;
		}
	}
}
std::vector<Card> Deck::GetStartingHand() {
	std::vector<Card> startingHand;
	for (uint32_t i = 0; i < 7; ++i) {
		startingHand.push_back(PopTopCard());
	}
	return startingHand;
}