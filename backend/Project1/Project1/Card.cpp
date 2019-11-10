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
	_cvv = cvv;
	CardProxy c = CardProxy(*this);
	c.do_setCVV(cvv);
}
unsigned int  Card::do_getPIN() const
{
	return _pin;
}
void   Card::do_setPIN(unsigned int pin)
{
	_pin = pin;
	CardProxy c = CardProxy(*this);
	c.do_setPIN(pin);
}
std::string  Card::do_getName()const
{
	return _name;
}
void  Card::do_setName(std::string name)
{
	_name = name;
	CardProxy c = CardProxy(*this);
	c.do_setName(name);
}
unsigned long  Card::do_getBalance() const
{
	return _balance;
}
void  Card::do_setBalance(unsigned long bal)
{
	_balance = bal;
	CardProxy c = CardProxy(*this);
	c.do_setBalance(bal);
}

const std::vector< ICard::Transaction>&  Card::do_getTransactions()const
{
	return _transactions;
}

void  Card::do_setTransactions( std::vector<Card::Transaction>& tr)
{
	_transactions = tr;
	CardProxy c = CardProxy(*this);
	c.do_setTransactions(tr);
}

const std::vector< Card::Transaction>&  Card::do_getTemplates()const
{
	return _templates;
}

void  Card::do_setTemplates( std::vector<Card::Transaction>& tm)
{
	_templates = tm;
	CardProxy c = CardProxy(*this);
	c.do_setTemplates(tm);
}

void  Card::do_addTemplate(const Card::Transaction& tm)
{
	_templates.insert(_templates.begin(), 1, tm);
	CardProxy c = CardProxy(*this);
	c.do_addTemplate(tm);
}

void  Card::do_addTransaction(const Card::Transaction& tr)
{
	_transactions.insert(_transactions.begin(), 1, tr);
	CardProxy c = CardProxy(*this);
	c.do_addTransaction(tr);
}


void Card::do_setDate(std::string dt)
{
	_endDate = dt;
	CardProxy c = CardProxy(*this);
	c.do_setDate(dt);
}

std::string Card::do_getDate()const
{
	return _endDate;
}


std::ostream & Card::do_print(std::ostream & os) const
{
	os << "Card Number :" << (*this).do_getNumber() << '\n'
		<< "CVV :" << (*this).do_getCVV() << '\n'
		<< "PIN :" << (*this).do_getPIN() << '\n'
		<< "Name :" << (*this).do_getName() << '\n'
		<< "End Date :" << (*this).do_getDate() << '\n'
		<< "Balance :" << (*this).do_getBalance();
	return os;
}

std::ostream& operator<<(std::ostream&os, const Card::Transaction& tr)
{
	os << "Date :" << (tr.getDate()) << '\n'
		<< "Sender Card Num :" << tr.getSenderCardNum() << '\n'
		<< "Reciever Card Num :" << tr.getrecieverCardNum() << '\n'
		<< "Sum :" << tr.getSum() << '\n'
		<< "Description :" << tr.getDescription();
	return os;

}

