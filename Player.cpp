#include <iostream>
#include "Player.h"
#include <string.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

using namespace std;


Player::Player(string name):
	m_cards_sum(0),m_lose_rounds(0),m_win_rounds(0),cnt_cards(0),cnt_draws(0)
{
	m_name = name;
}


Player::~Player() 
{
	
};
string Player:: get_name()const {
	return m_name;
}

void Player::set_name( string str)
{
	if (str.empty()) return;
	m_name = str;
}

void Player::calc_sum(Card** arr) 
{
	m_cards_sum = 0;
	int cnt_ace=0;
	for(int i=0; i<cnt_cards; i++)
	{
		m_cards_sum += arr[i]->get_card_game();
		if (arr[i]->get_card_val() == 1)
			cnt_ace++;
	}

	while (m_cards_sum > 21 &&cnt_ace>0) {
		m_cards_sum -= 10;
		cnt_ace--;
	}

}

char Player::get_sum() const
{
	return m_cards_sum;
}

void Player::inc_wins()
{
	m_win_rounds++;
}

void Player::inc_loses()
{
	m_lose_rounds++;
}

char Player::get_wins() const
{
	return m_win_rounds;
}
char Player:: get_cntCards() const
{
	return cnt_cards;
}
void Player:: set_cntCards(bool b)
{
	if (b)
		cnt_cards++;
	else cnt_cards--;
}


char Player::get_loses() const
{
	return m_lose_rounds;
}

char Player::get_draws()const {
	return cnt_draws;
}
void Player::set_draws(bool b){
	if (b)cnt_draws++;
	else cnt_draws=0;
}
//////////Not member if the Player class///////

ostream& operator<<(ostream& os, const Player& p)// not void -change it 
{
	os << p.m_name;
	return os;
}