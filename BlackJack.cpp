#include "BlackJack.h"
#include <iostream>
#include <string>
using namespace std;
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


#define MAX_CARDS_PLAYER 6
#define MAX_VAL_DEALER 16
#define DEALER "Dealer"



BlackJack::BlackJack() :
	m_main_d(52), d_passed_sum(false), end_round_p(false), end_round_f(false),m_inner_rounds(0)
{
	m_c_player = new Card* [MAX_CARDS_PLAYER];
	m_c_dealer = new Card*[MAX_CARDS_PLAYER];
	m_rounds = 0;
	m_dealer = new Player("Dealer");
	m_player = new Player;

}

BlackJack::~BlackJack() 
{
	delete[] m_c_player;
	delete[] m_c_dealer;
	delete m_dealer;
	delete m_player;
};


void BlackJack::play() {
	cout << "Hi, please enter your name" << endl;
	string name;
	cin >> name;
	m_player->set_name(name);
	while (choice())	
	{
		if (m_inner_rounds == 0) {

			
			round_Operations(m_c_dealer, m_dealer);
			round_Operations(m_c_player, m_player);
			printStatus(m_c_dealer, m_dealer);
			printStatus(m_c_player, m_player);
			m_inner_rounds++;
			round_Operations(m_c_dealer, m_dealer);
			if (!d_passed_sum)
				printStatus(m_c_dealer, m_dealer);
			if (check_end_round()) end_round_f = true;

		}
		while(!end_round_f && m_inner_rounds>0)
		{
			if(Innerchoice())
			{
				round_Operations(m_c_player, m_player);
				round_Operations(m_c_dealer, m_dealer);
				m_inner_rounds++;
				printStatus(m_c_player, m_player);
				if (!d_passed_sum)
					printStatus(m_c_dealer, m_dealer);// here i want to print the player before the dealer, if dealer needed to be printed
				end_round_f = check_end_round();

			}
			else 
			{
				end_round_p = true;
				if (!d_passed_sum)//!check who won when dealer sum of cards smaller  than 17
				{
					round_Operations(m_c_dealer, m_dealer);
					if (!d_passed_sum)
						printStatus(m_c_dealer, m_dealer);
					if (!end_round_p)
						printStatus(m_c_player, m_player);
				}
				end_round_f = check_end_round();										
				if(!end_round_f) end_round_f = check_end_round_p();//need only if both <=21 
			}	
		}
		inits_next_round();
	}
	cout << "Out of " << (int)m_rounds << " rounds, you won "
		<< (int)m_player->get_wins() << " times and lost " 
		<<(int)m_player->get_loses() << " times \n";
	cout << "Bye Bye" << endl;
}





bool BlackJack::check_end_round()
{
	if (m_dealer->get_sum() > 21 && m_player->get_sum()<21)
	{
		end_round_Ops(m_player, m_dealer);

		return true;
	}

	if (m_player->get_sum() > 21 && m_dealer->get_sum() < 21)
	{
		end_round_Ops(m_dealer, m_player);
	
		return true;
	}
	if (m_dealer->get_sum() > 21 && m_player->get_sum() > 21) {
		if (m_dealer->get_sum() < m_player->get_sum())
		{
			end_round_Ops(m_player, m_dealer);
			return true;
		}
			
		else {
			end_round_Ops(m_dealer, m_player);
			return true;
		}
	}
	
	return false; //both sums smaller than 21
}

void BlackJack::inits_next_round()
{
	m_inner_rounds = 0;
	end_round_p = false;
	d_passed_sum = false;
	end_round_f = false;
	m_dealer->set_draws(false);
	m_player->set_draws(false);
	m_rounds++;
	return_cards();//return missing cards to the pack 
	m_player->calc_sum(m_c_player);
	m_dealer->calc_sum(m_c_dealer);
	m_main_d.reshuffle();//here pack must have 52 cards 
}

void BlackJack::return_cards()
{

	while ((m_player->get_cntCards()>0) || (m_dealer->get_cntCards()>0))
	{
		if(m_dealer->get_cntCards()>0)
		{
			m_main_d.push_front(m_c_dealer[m_dealer->get_cntCards()-1]);
			m_dealer->set_cntCards(false);
		}
		if (m_player->get_cntCards()>0)
		{
			m_main_d.push_front(m_c_player[m_player->get_cntCards() - 1]);
			m_player->set_cntCards(false);
		}
	}
}



bool BlackJack::check_end_round_p()//check if player doesn't want to take card from pile
{
	//wins
	if ((m_player->get_sum() <= 21) && (m_player->get_sum() > m_dealer->get_sum())) //player wins
	{
		end_round_Ops(m_player,m_dealer);
	}

	else if ((m_dealer->get_sum() <= 21) && (m_dealer->get_sum() > m_player->get_sum())) //dealer wins
	{
		end_round_Ops(m_dealer, m_player);
	}
	
	//tie
	else cout << "It's a tie! No one wins" << endl;
	return true;

}

bool choice() 
{
	unsigned choice;
	do 
	{
		cout << "Choose option\n"
			"1. New round\n"
			"2. Quit game" << endl;
		cin >> choice;
	} while ((choice > 2) && (choice < 1));
	return choice == 1;
}

bool Innerchoice() {
	unsigned choice;
	do {
		cout << "Choose option\n"
			"1. Take a card from the pile\n"
			"2. No more cards" << endl;
		cin >> choice;
	} while ((choice > 2) && (choice < 1));
	return choice == 1;
}

void BlackJack::round_Operations(Card** m_c_p, Player* m_p)
{
	int i;
	switch ( m_p->get_draws())
	{
	case 0:		i = 2;      // for first draw
		break;
	default:	i = 1;	 // for other drwas
		break;
	}
	if ((m_p->get_name() == DEALER && m_p->get_sum() <= MAX_VAL_DEALER) || m_p->get_name()!=DEALER)
	{

		while (i)
		{
			m_c_p[m_p->get_cntCards()] = m_main_d.pop_front();
			m_p->set_cntCards(true);
			i--;

		}

		if (m_p->get_name()==DEALER && (m_p->get_sum() > MAX_VAL_DEALER))
			d_passed_sum = 1;
		m_p->calc_sum(m_c_p);

		m_p->set_draws(true);
	}
	else if(m_p->get_name() == DEALER && m_p->get_sum() > MAX_VAL_DEALER){
		 d_passed_sum = 1;
	}
}



void BlackJack:: printStatus(Card** playerDeck,  Player* p) const
{
	cout << *p;
	cout << " cards:" << endl;
	
	for(int i=0;i<p->get_cntCards();i++)
	{

		cout << *playerDeck[i];
		cout << " ";
		
		
	}
	cout << " (Total of " << (int)p->get_sum() << ")" << endl;
}

void BlackJack:: end_round_Ops(Player* p_won, Player* p_lost) {
	cout << *p_won;
	cout << " wins" << endl;
	p_won->inc_wins();
	p_lost->inc_loses();
	
}
