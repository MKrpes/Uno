#pragma once

enum CardColors
{
	Red=50,Yellow,Green,Blue,Wildcard
};
enum CardTypes
{
	ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,Skip,Reverse,DrawTwo,ColorChange,DrawFour
};

class Card
{
public:
	CardColors Color;
	CardTypes Type;

	Card(CardColors color, CardTypes type) {
		Type = type;
		Color = color;
	}
	const CardColors getColor() const { return Color; }
	const CardTypes getType() const { return Type; }
};

