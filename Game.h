#pragma once
#include<vector>
#include<memory>
#include"Player.h"
#include"Deck.h"
#include"PlayedCards.h"
#include"Bot.h"


class Game
{
public:
	std::vector<std::unique_ptr<Player>> players;
	int turnOrder = 1;
	int currentPlayer = 0;
	uint32_t playerCount;
	uint32_t drawSum=0;



	Deck* deck;
	PlayedCards* playedCards;
	
	~Game();
	
	void nextPlayer();
	void turn();
	void processMove(Card card);
	bool checkIfVaildMove(Card card);
	int colorChange();
public:
	Game(uint32_t i);
};

