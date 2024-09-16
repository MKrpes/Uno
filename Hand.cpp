#include "pch.h"
#include "Hand.h"

bool compareCards(Card &card1, Card &card2) {
	if (card1.getColor() == card2.getColor()) {
		return card1.getType() < card2.getType();
	}
	else {
		return card1.getColor() < card2.getColor();
	}
}

Hand::Hand(std::vector<Card> drawnCards) {
	hand = drawnCards;
	Sort();
}

Hand::~Hand() {
	hand.clear();
}

void Hand::Sort() {
	std::sort(hand.begin(), hand.end(), compareCards);
}

void Hand::RemoveCard(UINT i) {
	hand.erase(hand.begin() + i);
}

void Hand::AddCard(const Card card) {
	hand.push_back(card);
	Sort();
}

std::vector<UINT> Hand::CheckForAvailableCards(const Card card) {
	std::vector<UINT> possibleMoves;
	for (UINT i = 0; i < hand.size(); ++i) {
		if (hand[i].getColor() == card.getColor() || hand[i].getType() == card.getType() || hand[i].getColor()==Wildcard) {
			possibleMoves.push_back(i);
		}
	}
	return possibleMoves;
}
std::vector<UINT> Hand::CheckForStackingCards(const Card card) {
	std::vector<UINT> possibleMoves;
	for (UINT i = 0; i < hand.size(); ++i) {
		if (hand[i].getType() == card.getType()) {
			possibleMoves.push_back(i);
		}
	}
	return possibleMoves;
}