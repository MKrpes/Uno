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
	uint32_t playerCount;
	uint32_t drawSum=0;


	//Scoreboard scBoard;
	Deck* deck;
	PlayedCards* playedCards;
	
	~Game();
	
	std::vector<Card> getPlayerhand();
	void nextPlayer();
	bool Playerturn(int i);
	void processMove(Card card);
	bool checkIfValidMove(Card card);
	void colorChange(Card card);
	void DrawCard();
	Game(SavedGameSettings& gameSet);
};

