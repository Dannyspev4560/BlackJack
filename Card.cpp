#include <iostream>
#include "Card.h"
#include <stdlib.h> 
#include <string>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


using namespace std;

char Card::m_cards_cnt(0);
char Card::m_cards_type[13]={0};//change to arr
const char Card::cards_max(52);
const char Card::card_type_max(4);


Card::Card(int card_val) //Constructor
{
	m_card_val = (char)card_val;
	m_cards_cnt++;
	m_cards_type[card_val - 1]++;
	if ((m_card_val >= 11) && (m_card_val <= 13))
		m_card_game = 10;
	else if (m_card_val == 1)
		m_card_game = 11;//Starting game value for ase
	else m_card_game = card_val;
}

Card::~Card() //Destructor
{
	m_cards_cnt--;
	//TODO ask yael
	//m_cards_type[m_card_val]--;
	//delete[] m_cards_type;
	
}

char Card:: get_card_val() const 
{
	return m_card_val;
}

Card::Card(const Card& c) //Copy Constructor
{
	m_card_val = c.m_card_val;
	m_cards_cnt++;
	m_cards_type[m_card_val]++;
	m_card_game = c.m_card_game;
}

int Card::toss_val() //Get random num 
{
	//Generate secret number between 1 and 13: 
	int val = rand() % 13 + 1;
	while (m_cards_type[val-1] == 4)
		val = rand() % 13 + 1;
	return val;
}



char Card::get_card_game() const
{
	return m_card_game;
}

//////////Not member if the Card class///////
ostream& operator<<(ostream& os, const Card& c)
{
	if (c.m_card_val == 1)
		 return(os<< "A");
	if (c.m_card_val == 11)
		return(os << "J");
	if (c.m_card_val == 12)
		return(os << "Q");
	if (c.m_card_val == 13)
		return(os << "K");
	if (c.m_card_val == 10)
		return(os << "10");
	return (os<<(int)c.m_card_val);
}



	




