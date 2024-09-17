#include "pch.h"
#include "Bot.h"
#include"Player.h"


//Bot::Bot(const std::vector<Card> cards){
//	playerHand = new Hand(cards);
//}

UINT Bot::ReturnHighestPriority(Card card, int drawsum)
{
	if (drawsum == 0) {
		std::vector<UINT> possibleMoves = playerHand->CheckForAvailableCards(card);
		if (possibleMoves.empty()) { //no possible moves, draws card
			return -1;
		}
		else if (possibleMoves.size() == 1) { //only possible move
			return possibleMoves[0];
		}
		else {
			std::map<CardColors, UINT> colorCount = ColorCount();
			UINT choice = possibleMoves[0];
			for (UINT i : possibleMoves) {
				if (playerHand->hand.at(i).Type > playerHand->hand.at(choice).Type && 
					colorCount[playerHand->hand.at(i).Color]> colorCount[playerHand->hand.at(choice).Color]) {

						choice = i;
				}
			}
			return choice;
		}
	}
	else {
		std::vector<UINT> possibleMoves = playerHand->CheckForStackingCards(card);
		if (possibleMoves.empty()) { //no possible moves, draws card
			return -1;
		}
		else if (possibleMoves.size() == 1) { //only possible move
			return possibleMoves[0];
		}
		else {
			std::map<CardColors, UINT> colorCount = ColorCount();
			UINT choice = possibleMoves[0];
			for (UINT i : possibleMoves) {
				if (playerHand->hand.at(i).getType() > playerHand->hand.at(choice).getType() &&
					colorCount[playerHand->hand.at(i).getColor()] > colorCount[playerHand->hand.at(choice).getColor()]) {
						choice = i;
				}
			}
			return choice;
		}
	}
}

std::map<CardColors, UINT> Bot::ColorCount(bool countsWildcards)
{
	std::map<CardColors, UINT> colorCount;
	if (countsWildcards) {
		for (Card i : playerHand->hand) {
			colorCount[i.getColor()]++;
		}
	}
	else
	{
		for (Card i : playerHand->hand) {
			if (i.getColor() != Wildcard) {
				colorCount[i.getColor()]++;
			}
			else {
				break;
			}
		}
	}
	return colorCount;
}

CardColors Bot::ChooseColorToChange()
{
	return ColorCount(false).begin()->first;
}

