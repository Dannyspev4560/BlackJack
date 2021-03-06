#ifndef  PILE_H_
#define  PILE_H_

class Card;

class Dequeue
{
protected:
	char m_size;
	char m_capacity;
	Card** m_queue;
	char m_left;
	char m_right;
	
public:
	Dequeue(char size=0);
	~Dequeue();
	void push_back( Card* c);
	Card* pop_back();
	void push_front(Card* c);
	Card* pop_front();
	Card* front() const;
	Card* back() const;
	char size() const;
	bool is_empty() const;
	void reshuffle();
};

class Pile :Dequeue {
public:
	void new_Pile(int size,bool isEmpty);//no ctor?
};


#endif // Pile_H_