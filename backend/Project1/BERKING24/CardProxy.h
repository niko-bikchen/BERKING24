#pragma once
#include "Card.h"


class Card::CardProxy :public ICard
{
	friend class Card;
private:
	Card& _card;

	CardProxy(Card& c) :_card(c)
	{

	}

	void do_setDate(std::string);
	std::string do_getDate()const;
	void do_setNumber(std::string);
	std::string do_getNumber()const;
	unsigned int do_getCVV()const;
	void do_setCVV(unsigned int);
	unsigned int do_getPIN() const;
	void  do_setPIN(unsigned int);
	std::string do_getName()const;
	void do_setName(std::string);
	unsigned long do_getBalance() const;
	void do_setBalance(unsigned long);
	const std::vector<Transaction>& do_getTransactions()const;
	void do_setTransactions(std::vector<Transaction>&);
	const std::vector<Transaction>& do_getTemplates()const;
	void do_setTemplates(std::vector<Transaction>&);
	void do_addTemplate(const Transaction&);
	void do_addTransaction(const Transaction&);
	std::ostream& do_print(std::ostream&)const;


public:


};
