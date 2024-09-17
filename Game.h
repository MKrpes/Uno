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
	void PlayerMove(const int i,int color=0);
	void processMove();
	bool checkIfValidMove(Card card) const;
	void drawSumDraw();
	void DrawCard();
	void PlayerUNOdraw();
	
	Game(SavedGameSettings& gameSet);

	void GameFlow();


private:
	void nextPlayer();
	void BotMove(UINT i, Bot* currentBot);
	void colorChange(Card* card, Bot* currentBot);
	void outOfCards();
	Bot* getCurrentBot();
};

