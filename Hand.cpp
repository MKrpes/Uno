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

void Hand::RemoveCard(uint32_t i) {
	hand.erase(hand.begin() + i);
}

void Hand::AddCard(const Card card) {
	hand.push_back(card);
	Sort();
}

std::vector<uint32_t> Hand::CheckForAvailableCards(const Card card) {
	std::vector<uint32_t> possibleMoves;
	for (uint32_t i = 0; i < hand.size(); ++i) {
		if (hand[i].getColor() == card.Color || hand[i].getType() == card.Type || hand[i].getColor()==54) {
			possibleMoves.push_back(i);
		}
	}
	return possibleMoves;
}
std::vector<uint32_t> Hand::CheckForStackingCards(const Card card) {
	std::vector<uint32_t> possibleMoves;
	for (uint32_t i = 0; i < hand.size(); ++i) {
		if (hand[i].getType() == card.Type) {
			possibleMoves.push_back(i);
		}
	}
	return possibleMoves;
}