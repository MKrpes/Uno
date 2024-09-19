#pragma once
#include<vector>
#include<memory>
#include"Player.h"
#include"Deck.h"
#include"PlayedCards.h"
#include"Bot.h"
#include"SavedGameSettings.h"
#include"Scoreboard.h"
#include"Card.h"

class Game
{
	friend class View;
public:
	std::vector<Player> players;
	int turnOrder = 1;
	int currentPlayer = 0;
	UINT playerCount;
	UINT drawSum=0;


	Scoreboard scBoard;
	Deck deck;
	PlayedCards playedCards;

	Game() {};
	~Game() {};

	std::vector<Card>& getPlayerhand();
	
	int validatePlayerMove(int i);
	bool PlayerMove(const int i,int color=0);
	bool processMove();
	bool checkIfValidMove(const Card card);
	void DrawCard();
	void PlayerUNOdraw();

	Game(SavedGameSettings& gameSet);

	bool UpdatePoints();


private:
	void drawSumDraw();
	void nextPlayer();
	void outOfCards();
	
	bool WinCheck() const;
	void resetGame(const bool rndWin);

	bool BotMove(UINT i);
	void colorChange(Card* card);
};

