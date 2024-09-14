#include "pch.h"
#include "Game.h"

Game::Game(SavedGameSettings& gameSet) {
	playerCount = gameSet.playerCount;
	deck = new Deck();
	playedCards = new PlayedCards(deck->PopTopCard());
	players.push_back(std::make_unique<Player>(deck->GetStartingHand()));
	for (uint32_t i=1; i < playerCount; ++i) {
		players.push_back(std::make_unique<Bot>(deck->GetStartingHand()));
	}
}

std::vector<Card> Game::getPlayerhand()
{
	return players[0]->playerHand->hand;
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
			colorChange(card);
			break;
		}
		case 14: {
			drawSum += 4;
			colorChange(card);
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

void Game::colorChange(Card card) { //!!!!!!!!
	 
}