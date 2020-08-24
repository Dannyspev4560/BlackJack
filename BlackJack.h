#ifndef  BLACKJACK_H_
#define BLACKJACK_H_
#include "Player.h"
#include "Dequeue.h"
#include "Card.h"
#include <iostream>
using namespace std;

class BlackJack
{
	Player* m_player;
	Player* m_dealer;
	Dequeue m_main_d;
	Card** m_c_player;
	Card** m_c_dealer;
	char  m_rounds;
	char m_inner_rounds;
	bool end_round_f;
	bool d_passed_sum;//for dealer if he passes total game value 16
	bool end_round_p;//for player if he decides to quit anytime
	void return_cards();
	void printStatus(Card** playerDeck, Player* p) const;
	bool check_end_round();
	void inits_next_round();
	bool check_end_round_p();
	void round_Operations(Card** m_c_player,Player* m_player);
	void end_round_Ops(Player* p_won, Player* p_lost);


public:
	BlackJack();
	~BlackJack();
	void play();
};
//external functions
bool choice();
bool Innerchoice();


#endif // BLACKJACK_H_

