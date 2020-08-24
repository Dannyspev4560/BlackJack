#ifndef  CARD_H_
#define  CARD_H_
#include <iostream>
#include <string>
using namespace std;

class Card
{
	char m_card_game;//from 1 to 11-used for the game
	char m_card_val;//from 1 to 13 to represent each card name

	static char m_cards_cnt;
	static char m_cards_type[13];
	const static char cards_max;
	const static char card_type_max;

public:
	Card(int card_val); //Constructor
    ~Card(); //Destructor
	Card(const Card& c); //Copy Constructor
	static int toss_val(); //Get random value to card
	char get_card_val() const;
	friend ostream& operator<<(ostream& os, const Card& c);
	char get_card_game() const;
};


	

#endif // CARD_H_
