#include "Game.h"

Game::Game(uint32_t n) {
	playerCount = n;
	deck = new Deck();
	playedCards = new PlayedCards(deck->PopTopCard());
	players.push_back(std::make_unique<Player>(deck->GetStartingHand()));
	for (uint32_t i=0; i < n; ++i) {
		players.push_back(std::make_unique<Bot>(deck->GetStartingHand()));
	}
}

void Game::nextPlayer() {
	currentPlayer = currentPlayer + turnOrder;
	if (currentPlayer > (int)playerCount) { currentPlayer = 0; return;}
	if (currentPlayer < 0) { currentPlayer = playerCount - 1; return;}
}

void Game::processMove(Card card) {
	if (checkIfVaildMove(card)) {
		switch (card.getType()) {
		case 10: {
			nextPlayer();
			break;
		}
		case 11: {
			turnOrder = -turnOrder;
			break;
		}
		case 12: {
			drawSum += 2;
			break;
		}
		case 13: {
			colorChange();
			break;
		}
		case 14: {
			drawSum += 4;
			colorChange();
			break;
		}
		}
	}
}

bool Game::checkIfVaildMove(Card card) {
	if (playedCards->getLast().Color == card.getColor() ||
		playedCards->getLast().Type == card.getType() ||
		card.getColor() == 4) {
		return true;
	}
	return false;
}

int Game::colorChange() { //!!!!!!!!
	return 0;
}