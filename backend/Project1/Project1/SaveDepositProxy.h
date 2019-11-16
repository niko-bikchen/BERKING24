#pragma once
#include "SaveDeposit.h"

class SaveDeposit::SaveDepositProxy
{
	friend class SaveDeposit;
private:
	SaveDeposit& _deposit;

	SaveDepositProxy(SaveDeposit& c) :_deposit(c)
	{

	}

	void do_setBalance(unsigned long);
	void do_setCard(std::string);
	void do_setStartDate(std::string);
	void do_setEndDate(std::string date);
	

	
public:
	
};
