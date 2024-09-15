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

std::vector<Card>& Game::getPlayerhand()
{
	return players[0]->playerHand->hand;
}

void Game::nextPlayer() {
	currentPlayer = currentPlayer + turnOrder;
	if (currentPlayer > (int)playerCount) { currentPlayer = 0; return;}
	if (currentPlayer < 0) { currentPlayer = playerCount - 1; return;}
}

int Game::validatePlayerMove(int i)
{

	if (checkIfValidMove(getPlayerhand()[i])) {
		if (getPlayerhand()[i].getColor() == Wildcard) {
			return 1; //requires chooseColorDlg to run
		}
		return 0; //normal valid move
	}
	else return -1; //invalid move
	
}

void Game::PlayerMove(int i, int color)
{
	players[0]->hasDrawn = false;
if (getPlayerhand()[i].getColor() == Wildcard) {
		getPlayerhand()[i].Color = (CardColors)color;
	}
	playedCards->playerTurn(getPlayerhand()[i]);
	getPlayerhand().erase(getPlayerhand().begin()+i);
}

void Game::processMove(Card card) {
	if (checkIfValidMove(card)) {
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

bool Game::checkIfValidMove(Card card) const{
	if (playedCards->getLast().Color == card.getColor() ||
		playedCards->getLast().Type == card.getType() ||
		card.getColor() == Wildcard) {
		return true;
	}
	return false;
}



void Game::colorChange(Card card) { //!!!!!!!!
	 
}

void Game::DrawCard()
{
	if (!players[currentPlayer]->hasDrawn) {
		players[currentPlayer]->playerHand->AddCard(deck->PopTopCard());
		players[currentPlayer]->hasDrawn = true;
	}
}
