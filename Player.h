#ifndef  PLAYER_H_
#define  PLAYER_H_
#include <string>
#include "Card.h"
#include <iostream>
using namespace std;

class Player
{
	string m_name;
	char m_cards_sum;
	char m_win_rounds;
	char m_lose_rounds;
	char cnt_cards;
	char cnt_draws;

public:
	Player(string name="");
	~Player();
	void set_name(string str);
	void calc_sum(Card** arr );
	char get_sum() const;//const
	char get_cntCards() const;
	void set_cntCards(bool b);
	void inc_wins();
	void inc_loses();
	void set_draws(bool b);
	string get_name()const;
	char get_draws() const;
	char get_wins() const; 
	char get_loses() const; 


	//////////Not member if the Player class///////
	friend ostream& operator<<(ostream& os, const Player& p);

};


#endif // PLAYER_H_
