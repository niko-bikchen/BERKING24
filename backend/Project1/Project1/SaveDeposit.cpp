#include "SaveDeposit.h"
#include "SaveDepositProxy.h"


unsigned long SaveDeposit::do_getBalance() const
{
	return _sum;
}

void SaveDeposit::do_setBalance(unsigned long sum)
{
	_sum = sum;
	SaveDepositProxy c = SaveDepositProxy(*this);
	c.do_setBalance(sum);
}

std::ostream & SaveDeposit::do_print(std::ostream & os) const
{
	os << "Card Number :" << this->do_getCardNum() << '\n'
		<< "Start Date :" << this->do_getStartDate() << '\n'
		<< "End Date :" << this->do_getEndDate();
	return os;
}

void SaveDeposit::do_setCard(std::string card)
{
	
	SaveDepositProxy c = SaveDepositProxy(*this);
	c.do_setCard(card);
	_cardNum = card;
}

std::string SaveDeposit::do_getCardNum() const
{
	return _cardNum;
}

std::string SaveDeposit::do_getStartDate() const
{
	return _startDate;
}

void SaveDeposit::do_setStartDate(std::string sd)
{
	_startDate = sd;
	SaveDepositProxy c = SaveDepositProxy(*this);
	c.do_setStartDate(sd);
}

std::string SaveDeposit::do_getEndDate() const
{
	return _endDate;
}

void SaveDeposit::do_setEndDate(std::string date)
{
	_endDate = date;
	SaveDepositProxy c = SaveDepositProxy(*this);
	c.do_setEndDate(date);
}
//TODO firstly need to implement db and IDepositManager
void SaveDeposit::do_endDeposit()
{
}


