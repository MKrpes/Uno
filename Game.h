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
	std::vector<std::unique_ptr<Player>> players;
	int turnOrder = 1;
	int currentPlayer = 0;
	UINT playerCount;
	UINT drawSum=0;


	Scoreboard* scBoard;
	Deck* deck;
	PlayedCards* playedCards;
	
	~Game();
	
	std::vector<Card>& getPlayerhand();
	
	int validatePlayerMove(int i);
	bool PlayerMove(const int i,int color=0);
	bool processMove();
	bool checkIfValidMove(Card card) const;
	void DrawCard();
	void PlayerUNOdraw();
	
	Game(SavedGameSettings& gameSet);

	bool UpdatePoints();


private:
	void drawSumDraw();
	void nextPlayer();
	bool BotMove(UINT i, Bot* currentBot);
	void colorChange(Card* card, Bot* currentBot);
	void outOfCards();
	Bot* getCurrentBot();
	bool WinCheck() const;
	void resetGame(const bool rndWin);
};

