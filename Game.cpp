#include "pch.h"
#include "Game.h"

Game::Game(SavedGameSettings& gameSet) {
	playerCount = gameSet.playerCount;
	deck = new Deck();
	playedCards = new PlayedCards(deck->PopTopNSCard());
	players.push_back(std::make_unique<Player>(deck->GetStartingHand()));
	for (UINT i=1; i < playerCount; ++i) {
		players.push_back(std::make_unique<Bot>(deck->GetStartingHand()));
	}
	switch (gameSet.GameType) {
	case 1: {
		scBoard = new Scoreboard(playerCount, (types)gameSet.GameType, gameSet.winsNeeded);
		break;
	}
	case 2: {
		scBoard = new Scoreboard(playerCount, (types)gameSet.GameType, gameSet.pointsNeeded);
		break;
	}default: {
		scBoard = new Scoreboard(playerCount, (types)0, gameSet.pointsNeeded);
	}
	}
}

bool Game::UpdatePoints()
{
	switch (scBoard->GetType()) {
	case 0:
		return scBoard->WritePoints(currentPlayer);
	case 1:
		return scBoard->WritePoints(currentPlayer);
	case 2:
	{
		int pointsSum = 0;
		for (UINT i = 0; i < playerCount;++i) {
			for (Card card : players[i]->playerHand->hand) {
				if (card.getType() < Skip) {
					pointsSum += card.getType();
					continue;
				}
				else if (card.getType() < ColorChange) {
					pointsSum += 20;
					continue;
				}
				else if (card.getType() >= ColorChange) {
					pointsSum += 40;
					continue;
				}
			}
		}
		return scBoard->WritePoints(currentPlayer, pointsSum);
	}
	}
}


Game::~Game()
{
	players.~vector();
	deck->~Deck();
	playedCards->~PlayedCards();
	scBoard->~Scoreboard();
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

bool Game::PlayerMove(const int i, int color)
{
	players[0]->hasDrawn = false;
	if (i != -1) {
		Card card = getPlayerhand()[i];
		switch (card.getType()) {
		case 10: {
			if (playerCount == 2) {
				playedCards->playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				if (WinCheck()) { return true; }
				else {
					return false;
				}
			}
			else {
				if (WinCheck()) { return true; }
				else {
					nextPlayer();
					nextPlayer();

					return false;
				}				
			}
			break;
		}
		case 11: {
			if (playerCount == 2) {
				playedCards->playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				if (WinCheck()) { return true; }
				else {
					return false;
				}
			}
			else {
				turnOrder = -turnOrder;
				playedCards->playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				if (WinCheck()) { return true; }
				else {
					nextPlayer();
					return false;
				}
			}
		}
		case 12: {
			drawSum += 2;
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;
			}
		}
		case 13: {
			card.Color = (CardColors)color;
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;
			}
		}
		case 14: {
			drawSum += 4;
			card.Color = (CardColors)color;
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;
			}
		}default:
		{
			playedCards->playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;		
			}
		}
		}

	}
	else {
		nextPlayer();
		return false;
	}
}

bool Game::processMove() {
	Bot* currentBot = getCurrentBot();
	currentBot->hasDrawn = false;
	int move = currentBot->ReturnHighestPriority(playedCards->getLast(), drawSum);
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
					return BotMove(move, currentBot);
				}
			}
			else {
				return BotMove(move, currentBot);
			}
		}
		else {
			DrawCard();
			move = currentBot->ReturnHighestPriority(playedCards->getLast());
			if(move == -1) {
				nextPlayer();
			}
			else {
				return BotMove(move, currentBot);
			}
		}
	}
	else {
		return BotMove(move, currentBot);
	}
	return false;
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

void Game::PlayerUNOdraw()
{
	for (int i = 0; i < 2; ++i) {
		if (deck->deck.empty()) {
			outOfCards();
		}
		players[0]->playerHand->AddCard(deck->PopTopCard());
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

bool Game::WinCheck() const
{
	return players[currentPlayer]->playerHand->hand.empty();
}

bool Game::BotMove(UINT i, Bot* currentBot)
{
	Card card = currentBot->PlayerTurn(i);
	switch (card.getType()) {
	case 10: {
		if (playerCount == 2) {
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);
			if (WinCheck()) return true;

		}
		else {
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);
			if (WinCheck()) return true;
			nextPlayer();
			nextPlayer();
		}
		break;
	}
	case 11: {
		if (playerCount == 2) {
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);
			if (WinCheck()) return true;

		}
		else {
			turnOrder = -turnOrder;
			currentBot->playerHand->RemoveCard(i);
			playedCards->playerTurn(card);
			if (WinCheck()) return true;
			nextPlayer();
		}
		break;
	}
	case 12: {
		drawSum += 2;
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}
	case 13: {
		colorChange(&card, currentBot);
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}
	case 14: {
		drawSum += 4;
		colorChange(&card, currentBot);
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}default:
		currentBot->playerHand->RemoveCard(i);
		playedCards->playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}
	return false;
}

void Game::resetGame(const bool rndWin)
{
	deck->~Deck();
	deck = new Deck();
	playedCards->~PlayedCards();
	playedCards = new PlayedCards(deck->PopTopNSCard());
	for (int i = 0; i < playerCount; ++i) {
		players[i]->playerHand->~Hand();
	}
	//players.push_back(std::make_unique<Player>(deck->GetStartingHand()));
	for (UINT i = 0; i < playerCount; ++i) {
		//players.push_back(std::make_unique<Bot>(deck->GetStartingHand()));
		players[i]->playerHand=new Hand(deck->GetStartingHand());
	}
	if (!rndWin) {
		types type = (types)scBoard->GetType();
		int reqPoints = scBoard->GetReqPoints();
		scBoard->~Scoreboard();
		scBoard = new Scoreboard(playerCount, type, reqPoints);
	}
}