#include "pch.h"
#include "Bot.h"
#include"Player.h"


//Bot::Bot(const std::vector<Card> cards){
//	playerHand = new Hand(cards);
//}

uint32_t Bot::ReturnHighestPriority(Card card)
{
	if (playerHand->CheckForAvailableCards(card).size()==0) { //no possible moves, draws card
		return -1;
	}
	else if(playerHand->CheckForAvailableCards(card).size() == 1){ //only possible move
		return playerHand->CheckForAvailableCards(card)[0];
	}
	else { 

	}
}

