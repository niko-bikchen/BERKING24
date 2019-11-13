#pragma once
#include "Card.h"
#include "CardProxy.h"


void Card::do_setNumber(std::string num)
{

	CardProxy c = CardProxy(*this);
	c.do_setNumber(num);
	_number = num;
}
std::string  Card::do_getNumber() const
{
	return _number;
}
unsigned int  Card::do_getCVV()const
{
	return _cvv;
}
void  Card::do_setCVV(unsigned int cvv)
{

	CardProxy c = CardProxy(*this);
	c.do_setCVV(cvv);
	_cvv = cvv;
}
unsigned int  Card::do_getPIN() const
{
	return _pin;
}
void   Card::do_setPIN(unsigned int pin)
{

	CardProxy c = CardProxy(*this);
	c.do_setPIN(pin);
	_pin = pin;
}
std::string  Card::do_getName()const
{
	return _name;
}
void  Card::do_setName(std::string name)
{

	CardProxy c = CardProxy(*this);
	c.do_setName(name);
	_name = name;
}
unsigned long  Card::do_getBalance() const
{
	return _balance;
}
void  Card::do_setBalance(unsigned long bal)
{

	CardProxy c = CardProxy(*this);
	c.do_setBalance(bal);
	_balance = bal;
}

const std::vector< ICard::Transaction>& Card::do_getTransactions()const
{
	return _transactions;
}

void  Card::do_setTransactions(std::vector<Card::Transaction>& tr)
{

	CardProxy c = CardProxy(*this);
	c.do_setTransactions(tr);
	_transactions = tr;
}

const std::vector< Card::Transaction>& Card::do_getTemplates()const
{
	return _templates;
}

void  Card::do_setTemplates(std::vector<Card::Transaction>& tm)
{

	CardProxy c = CardProxy(*this);
	c.do_setTemplates(tm);
	_templates = tm;
}

void  Card::do_addTemplate(const Card::Transaction& tm)
{

	CardProxy c = CardProxy(*this);
	c.do_addTemplate(tm);
	_templates.insert(_templates.begin(), 1, tm);
}

void  Card::do_addTransaction(const Card::Transaction& tr)
{

	CardProxy c = CardProxy(*this);
	c.do_addTransaction(tr);
	_transactions.insert(_transactions.begin(), 1, tr);
}


void Card::do_setDate(std::string dt)
{

	CardProxy c = CardProxy(*this);
	c.do_setDate(dt);
	_endDate = dt;
}

std::string Card::do_getDate()const
{
	return _endDate;
}


std::ostream& Card::do_print(std::ostream& os) const
{
	os << "Card Number :" << (*this).do_getNumber() << '\n'
		<< "CVV :" << (*this).do_getCVV() << '\n'
		<< "PIN :" << (*this).do_getPIN() << '\n'
		<< "Name :" << (*this).do_getName() << '\n'
		<< "End Date :" << (*this).do_getDate() << '\n'
		<< "Balance :" << (*this).do_getBalance();
	return os;
}

std::ostream& operator<<(std::ostream& os, const Card::Transaction& tr)
{
	os << "Date :" << (tr.getDate()) << '\n'
		<< "Sender Card Num :" << tr.getSenderCardNum() << '\n'
		<< "Reciever Card Num :" << tr.getrecieverCardNum() << '\n'
		<< "Sum :" << tr.getSum() << '\n'
		<< "Description :" << tr.getDescription();
	return os;

}

bool operator==(const ICard::Transaction& tr1, const ICard::Transaction& tr2)
{
	return (tr1.getDate() == tr2.getDate() &&
		tr1.getDescription() == tr2.getDescription() &&
		tr1.getrecieverCardNum() == tr2.getrecieverCardNum() &&
		tr1.getSenderCardNum() == tr2.getSenderCardNum() &&
		tr1.getSum() == tr2.getSum());
}

bool operator==(const ICard& c1, const ICard& c2)
{
	return (c1.getBalance() == c2.getBalance() &&
		c1.getCVV() == c2.getCVV() &&
		c1.getDate() == c2.getDate() &&
		c1.getName() == c2.getName() &&
		c1.getNumber() == c2.getNumber() &&
		c1.getPIN() == c2.getPIN() &&
		c1.getTemplates() == c2.getTemplates() &&
		c1.getTransactions() == c2.getTransactions());
}

