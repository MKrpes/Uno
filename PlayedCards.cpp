#include "pch.h"
#include "PlayedCards.h"

PlayedCards::PlayedCards(const Card card) {
	cardHistory.push_back(card);
}

PlayedCards::~PlayedCards()
{
	cardHistory.~vector();
}

std::vector<Card> PlayedCards::resetDeck()
{
	std::vector<Card> temp;
	temp.assign(cardHistory.begin(), cardHistory.end() - 1);
	cardHistory.erase(cardHistory.begin(), cardHistory.end() - 1);
	return temp;

}

void PlayedCards::playerTurn(const Card card) {
	cardHistory.push_back(card);
}
const Card PlayedCards::getLast() {
	return cardHistory.back();
}

