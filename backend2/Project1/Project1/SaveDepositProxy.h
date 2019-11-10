#pragma once
#include "SaveDeposit.h"

class SaveDeposit::SaveDepositProxy :public ISaveDeposit
{
	friend class SaveDeposit;
private:
	SaveDeposit& _deposit;

	SaveDepositProxy(SaveDeposit& c) :_deposit(c)
	{

	}

	unsigned long do_getBalance()const;
	void do_setBalance(unsigned long);
	std::ostream& do_print(std::ostream& out)const;
	void do_setCard(std::string);
	std::string do_getCardNum()const;
	std::string  do_getStartDate() const;
	void do_setStartDate(std::string);
	std::string do_getEndDate() const;
	void do_setEndDate(std::string date);
	void do_endDeposit();

	
public:
	
};
