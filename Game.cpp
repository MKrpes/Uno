#include "pch.h"
#include "Game.h"

Game::Game(SavedGameSettings& gameSet) : deck(), playedCards(deck.PopTopNSCard()),
playerCount(gameSet.playerCount), scBoard(playerCount,gameSet.GameType,gameSet.pointsNeeded)

{
	for (UINT i = 0; i < playerCount; ++i) {
		players.push_back(Player(deck.GetStartingHand()));
	}
}


bool Game::UpdatePoints()
{
	switch (scBoard.GetType()) {
	case 0:
		return scBoard.WritePoints(currentPlayer);
	case 1:
		return scBoard.WritePoints(currentPlayer);
	case 2:
	{
		int pointsSum = 0;
		for (UINT i = 0; i < playerCount; ++i) {
			for (Card card : players[i].playerHand.hand) {
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
		return scBoard.WritePoints(currentPlayer, pointsSum);
	}
	}
}



std::vector<Card>& Game::getPlayerhand()
{
	return players[0].playerHand.hand;
}

void Game::nextPlayer() {
	currentPlayer = currentPlayer + turnOrder;
	if (currentPlayer >= (int)playerCount) { currentPlayer = 0; return; }
	if (currentPlayer < 0) { currentPlayer = playerCount - 1; return; }
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
	players[0].hasDrawn = false;
	if (i != -1) {
		Card card = getPlayerhand()[i];
		switch (card.getType()) {
		case Skip: {
			if (playerCount == 2) {
				playedCards.playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				if (WinCheck()) { return true; }
				else {
					return false;
				}
			}
			else {
				if (WinCheck()) { return true; }
				else {
					playedCards.playerTurn(card);
					getPlayerhand().erase(getPlayerhand().begin() + i);
					nextPlayer();
					nextPlayer();

					return false;
				}
			}
			break;
		}
		case Reverse: {
			if (playerCount == 2) {
				playedCards.playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				if (WinCheck()) { return true; }
				else {
					return false;
				}
			}
			else {
				turnOrder = -turnOrder;
				playedCards.playerTurn(card);
				getPlayerhand().erase(getPlayerhand().begin() + i);
				if (WinCheck()) { return true; }
				else {
					nextPlayer();
					return false;
				}
			}
		}
		case DrawTwo: {
			drawSum += 2;
			playedCards.playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;
			}
		}
		case ColorChange: {
			card.Color = (CardColors)color;
			playedCards.playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;
			}
		}
		case DrawFour: {
			drawSum += 4;
			card.Color = (CardColors)color;
			playedCards.playerTurn(card);
			getPlayerhand().erase(getPlayerhand().begin() + i);
			if (WinCheck()) { return true; }
			else {
				nextPlayer();
				return false;
			}
		}default:
		{
			playedCards.playerTurn(card);
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
	players[currentPlayer].hasDrawn = false;
	int move = players[currentPlayer].ReturnHighestPriority(playedCards.getLast(), drawSum);
	if (move == -1) {
		if (drawSum != 0) {

			drawSumDraw();
			move = players[currentPlayer].ReturnHighestPriority(playedCards.getLast());
			if (move == -1) {

				DrawCard();
				move = players[currentPlayer].ReturnHighestPriority(playedCards.getLast());
				if (move == -1) {
					nextPlayer();
				}
				else {
					return BotMove(move);
				}
			}
			else {
				return BotMove(move);
			}
		}
		else {
			DrawCard();
			move = players[currentPlayer].ReturnHighestPriority(playedCards.getLast());
			if (move == -1) {
				nextPlayer();
			}
			else {
				return BotMove(move);
			}
		}
	}
	else {
		return BotMove(move);
	}
	return false;
}

bool Game::checkIfValidMove(const Card card) {
	if (playedCards.getLast().getColor() == card.getColor() ||
		playedCards.getLast().getType() == card.getType() ||
		card.getColor() == Wildcard) {

		return true;
	}
	return false;
}



void Game::colorChange(Card* card) {
	card->Color = players[currentPlayer].ChooseColorToChange();
}

void Game::DrawCard()
{
	if (!players[currentPlayer].hasDrawn) {
		if (deck.deck.empty()) {
			outOfCards();
		}
		players[currentPlayer].playerHand.AddCard(deck.PopTopCard());
		players[currentPlayer].hasDrawn = true;
	}
}

void Game::PlayerUNOdraw()
{
	for (int i = 0; i < 2; ++i) {
		if (deck.deck.empty()) {
			outOfCards();
		}
		players[0].playerHand.AddCard(deck.PopTopCard());
	}
}

void Game::drawSumDraw()
{
	for (UINT i = 0; i < drawSum; ++i) {
		if (deck.deck.empty()) {
			outOfCards();
		}
		players[currentPlayer].playerHand.AddCard(deck.PopTopCard());
	}
	drawSum = 0;
}

void Game::outOfCards()
{
	deck.Reset(playedCards.resetDeck());
}


bool Game::WinCheck() const
{
	return players[currentPlayer].playerHand.hand.empty();
}

bool Game::BotMove(UINT i)
{
	Card card = players[currentPlayer].PlayerTurn(i);
	switch (card.getType()) {
	case 10: {
		if (playerCount == 2) {
			players[currentPlayer].playerHand.RemoveCard(i);
			playedCards.playerTurn(card);
			if (WinCheck()) return true;

		}
		else {
			players[currentPlayer].playerHand.RemoveCard(i);
			playedCards.playerTurn(card);
			if (WinCheck()) return true;
			nextPlayer();
			nextPlayer();
		}
		break;
	}
	case 11: {
		if (playerCount == 2) {
			players[currentPlayer].playerHand.RemoveCard(i);
			playedCards.playerTurn(card);
			if (WinCheck()) return true;

		}
		else {
			turnOrder = -turnOrder;
			players[currentPlayer].playerHand.RemoveCard(i);
			playedCards.playerTurn(card);
			if (WinCheck()) return true;
			nextPlayer();
		}
		break;
	}
	case 12: {
		drawSum += 2;
		players[currentPlayer].playerHand.RemoveCard(i);
		playedCards.playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}
	case 13: {
		colorChange(&card);
		players[currentPlayer].playerHand.RemoveCard(i);
		playedCards.playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}
	case 14: {
		drawSum += 4;
		colorChange(&card);
		players[currentPlayer].playerHand.RemoveCard(i);
		playedCards.playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}default:
		players[currentPlayer].playerHand.RemoveCard(i);
		playedCards.playerTurn(card);
		if (WinCheck()) return true;
		nextPlayer();
		break;
	}
	return false;
}

void Game::resetGame(const bool rndWin)
{
	currentPlayer = 0;
	deck.newGame();
	playedCards.newGame(deck.PopTopNSCard());
	for (int i = 0; i < playerCount; ++i) {
		players[i].newGame(deck.GetStartingHand());
	}
	if (!rndWin) {
		scBoard.resetScoreboard();
	}
}