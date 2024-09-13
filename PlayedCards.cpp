#include "pch.h"
#include "PlayedCards.h"

PlayedCards::PlayedCards(const Card card) {
	cardHistory.push_back(card);
}

void PlayedCards::playerTurn(const Card card) {
	cardHistory.push_back(card);
}
const Card PlayedCards::getLast() {
	return cardHistory.back();
}