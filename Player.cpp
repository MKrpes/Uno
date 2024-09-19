#include "pch.h"
#include "Player.h"

Player::Player(const std::vector<Card>& cards) : playerHand(cards){
}


void Player::newGame(const std::vector<Card>& cards)
{
	playerHand.hand.clear();
	playerHand.hand = cards;
}

Card Player::PlayerTurn(int i) {
	return playerHand.hand[i];
}



int Player::ReturnHighestPriority(Card card, int drawsum)
{
	if (drawsum == 0) {
		std::vector<UINT> possibleMoves = playerHand.CheckForAvailableCards(card);
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
				if (playerHand.hand.at(i).getType() > playerHand.hand.at(choice).getType() &&
					colorCount[playerHand.hand.at(i).getColor()] > colorCount[playerHand.hand.at(choice).getColor()]) {

					choice = i;
				}
			}
			return choice;
		}
	}
	else {
		std::vector<UINT> possibleMoves = playerHand.CheckForStackingCards(card);
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
				if (playerHand.hand.at(i).getType() > playerHand.hand.at(choice).getType() &&
					colorCount[playerHand.hand.at(i).getColor()] > colorCount[playerHand.hand.at(choice).getColor()]) {
					choice = i;
				}
			}
			return choice;
		}
	}
}

std::map<CardColors, UINT> Player::ColorCount(bool countsWildcards)
{
	std::map<CardColors, UINT> colorCount;
	if (countsWildcards) {
		for (Card i : playerHand.hand) {
			colorCount[i.getColor()]++;
		}
	}
	else
	{
		for (Card i : playerHand.hand) {
			if (i.getColor() != Wildcard) {
				colorCount[i.getColor()]++;
			}
			else {
				break;
			}
		}
	}
	if (!colorCount.empty()) {
		return colorCount;
	}
	else {
		colorCount[Red] = 1;
		return colorCount;
	}
}

CardColors Player::ChooseColorToChange()
{
	std::map<CardColors, UINT> colorCount;
	colorCount = ColorCount(false);
	UINT mostCards = colorCount.begin()->second;
	CardColors cc = colorCount.begin()->first;
	for (const auto& pair : colorCount) {
		if (pair.second > colorCount[cc]) {
			cc = pair.first;
		}
	}
	return cc;
}

