#pragma once
#include "Card.h"


class Card::CardProxy 
{
	friend class Card;
private:
	Card& _card;

	CardProxy(Card& c) :_card(c)
	{

	}
	
	void do_setDate(std::string);
	void do_setNumber(std::string);
	void do_setCVV(unsigned int);
	void  do_setPIN(unsigned int);
	void do_setName(std::string);
	void do_setBalance(unsigned long);
	void do_setTransactions(std::vector<Transaction>&);
	void do_setTemplates(std::vector<Transaction>&);
	void do_addTemplate(const Transaction&);
	void do_addTransaction(const Transaction&);
	void do_deleteTemplate(const Card::Transaction&);


public:
	

};
