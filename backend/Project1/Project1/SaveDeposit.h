#pragma once


#include <string>"
#include "DefferedIDeposit.h"


class SaveDeposit :public ISaveDeposit
{
public:
	friend  DefferedISaveDeposit::DefferedISaveDeposit(std::string , std::string , std::string , unsigned long );
	

	~SaveDeposit() {}
private:
	SaveDeposit(std::string cN, std::string sD, std::string eD, unsigned long sum) :
		_cardNum(cN), _startDate(sD), _endDate(eD), _sum(sum)

	{

	}

	SaveDeposit& operator=(const SaveDeposit&);
	SaveDeposit(const SaveDeposit&);

	std::string _cardNum;
	std::string _startDate;
    std::string _endDate;
	unsigned long _sum;
	
	class SaveDepositProxy;
	 
	 unsigned long do_getBalance()const;
	 void do_setBalance(unsigned long);
	 std::ostream& do_print(std::ostream& out)const;
	 void do_setCard(std::string);
	 std::string do_getCardNum()const;
	 std::string  do_getStartDate() const;
	 void do_setStartDate(std::string);
	 std::string do_getEndDate() const;
	 void do_setEndDate(std::string date);

	
};

bool operator==(const ISaveDeposit&, const ISaveDeposit&);