#pragma once
#include <string>
#include "ICard.h"




class Card :public ICard
{
public:
	Card(std::string num, unsigned int cvv,  unsigned int pin, std::string name, std::string endDate,
		std::vector<Transaction> transaction , std::vector<Transaction> templates,unsigned long balance = 0) :
		_number(num),_cvv(cvv),_pin(pin),_name(name),_endDate(endDate),_balance(balance),
			_transactions(transaction),_templates(templates)
	{
	
	}
	
	~Card() {}

	
private:
	Card& operator=(const Card&);
	Card(const Card&);

	std::string _number;
	unsigned int _cvv;
	unsigned int _pin;
	std::string _name;
	std::string _endDate;
	unsigned long _balance;
	std::vector<Transaction> _transactions;
	std::vector<Transaction> _templates;

	class CardProxy;
	

	void do_setNumber(std::string);
	
	std::string do_getNumber() const;
	
	unsigned int do_getCVV()const;
	
	void do_setCVV(unsigned int );
	
	unsigned int do_getPIN() const;
	
	void  do_setPIN(unsigned int);
	
	std::string do_getName()const;
	
	void do_setName(std::string );
	
	unsigned long do_getBalance() const;
	
	void do_setBalance(unsigned long );
	

	const std::vector<Transaction>& do_getTransactions()const;
	

	void do_setTransactions( std::vector<Transaction>& );
	

	const std::vector<Transaction>& do_getTemplates()const;
	

	void do_setTemplates( std::vector<Transaction>& );
	

	void do_addTemplate(const Transaction& );
	

	void do_addTransaction(const Transaction& );


	 void do_setDate(std::string) ;
	 
	 std::string do_getDate()const;

	 std::ostream& do_print(std::ostream&)const;
	
};

std::ostream& operator<<(std::ostream&os, const ICard::Transaction&);

bool operator==(const ICard::Transaction&, const ICard::Transaction&);

bool operator==(const ICard&, const ICard&);
