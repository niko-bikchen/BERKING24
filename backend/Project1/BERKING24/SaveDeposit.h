#pragma once
#include "ISaveDeposit.h"

#include <string>"

class SaveDeposit :public ISaveDeposit
{
public:
	SaveDeposit(std::string cN, std::string sD, std::string eD, unsigned long sum) :
		_cardNum(cN), _startDate(sD), _endDate(eD), _sum(sum)

	{

	}

	//TODO firstly implement db and Depositmanager
	~SaveDeposit() {}
private:
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
	void do_endDeposit();

};

bool operator==(const ISaveDeposit&, const ISaveDeposit&);