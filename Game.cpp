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

void Game::GameGlow()
{
	while (currentPlayer != 0) {
		processMove();
	}
}



std::vector<Card>& Game::getPlayerhand()
{
	return players[0]->playerHand->hand;
}

void Game::nextPlayer() {
	currentPlayer = currentPlayer + turnOrder;
	if (currentPlayer >= (int)playerCount) { currentPlayer = 0; return;}
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

void Game::PlayerMove(const int i, int color)
{
	players[0]->hasDrawn = false;
	if (i != -1) {
		Card card = getPlayerhand()[i];
		switch (card.getType()) {
		case 10: {
			if (playerCount == 2) {
				playedCards->playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
			}
			else {
				nextPlayer();
				nextPlayer();
			}
			break;
		}
		case 11: {
			if (playerCount == 2) {
				playedCards->playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
			}
			else {
				turnOrder = -turnOrder;
				playedCards->playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				nextPlayer();
			}
			break;
		}
		case 12: {
			drawSum += 2;
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			nextPlayer();

			break;
		}
		case 13: {
			card.Color = (CardColors)color;
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			nextPlayer();

			break;
		}
		case 14: {
			drawSum += 4;
			card.Color = (CardColors)color;
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			nextPlayer();

			break;
		}default:
		{
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			nextPlayer();
			break;
		}
		}

	}
	else {
		nextPlayer();

	}
}

void Game::processMove() {
	Bot* currentBot = getCurrentBot();
	currentBot->hasDrawn = false;
	UINT move = currentBot->ReturnHighestPriority(playedCards->getLast(), drawSum);
	if (move==-1) {
		if (drawSum != 0) {

			drawSumDraw();
			move = currentBot->ReturnHighestPriority(playedCards->getLast());
			if (move == -1) {

				DrawCard();
				move = currentBot->ReturnHighestPriority(playedCards->getLast());
				if (move == -1) {
					nextPlayer();
				}
				else {
					BotMove(move, currentBot);
				}
			}
			else {
				BotMove(move, currentBot);
			}
		}
		else {
			DrawCard();
			if (currentBot->ReturnHighestPriority(playedCards->getLast()) == -1) {
				nextPlayer();
			}
			else {
				BotMove(move, currentBot);
			}
		}
	}
	else {
		BotMove(move, currentBot);
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



void Game::colorChange(Card* card, Bot* currentBot) { 
	card->Color = currentBot->ChooseColorToChange();
}

void Game::DrawCard()
{
	if (!players[currentPlayer]->hasDrawn) {
		if (deck->deck.empty()) {
			outOfCards();
		}
			players[currentPlayer]->playerHand->AddCard(deck->PopTopCard());
			players[currentPlayer]->hasDrawn = true;
	}
}

void Game::drawSumDraw()
{
	for (UINT i = 0; i < drawSum; ++i) {
		if (deck->deck.empty()) {
			outOfCards();
		}
		players[currentPlayer]->playerHand->AddCard(deck->PopTopCard());
	}
	drawSum = 0;
}

void Game::outOfCards()
{
	deck = new Deck(playedCards->resetDeck());
}

Bot* Game::getCurrentBot()
{
	return dynamic_cast<Bot*>(players[currentPlayer].get());
	
}

void Game::BotMove(UINT i, Bot* currentBot)
{
	Card card = currentBot->PlayerTurn(i);
	switch (card.getType()) {
	case 10: {
		if (playerCount == 2) {
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);

		}
		else {
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);
			nextPlayer();
			nextPlayer();
		}
		break;
	}
	case 11: {
		if (playerCount == 2) {
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);

		}
		else {
			turnOrder = -turnOrder;
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);
			nextPlayer();
		}
		break;
	}
	case 12: {
		drawSum += 2;
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		nextPlayer();
		break;
	}
	case 13: {
		colorChange(&card, currentBot);
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		nextPlayer();
		break;
	}
	case 14: {
		drawSum += 4;
		colorChange(&card, currentBot);
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		nextPlayer();
		break;
	}default:
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		nextPlayer();
		break;
	}
}

