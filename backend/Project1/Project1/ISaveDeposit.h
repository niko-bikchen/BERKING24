#pragma once
#include "IEntity.h"
#include <string>
#include <vector>

class ISaveDeposit:public IEntity
{
public:
	

	ISaveDeposit() {};
	virtual ~ISaveDeposit() {};

	std::string getStartDate() const
	{
		return do_getStartDate();
	}

	void setStartDate(std::string date)
	{
		return do_setStartDate(date);
	}

	std::string getEndDate() const
	{
		return do_getEndDate();
	}

	void setEndDate(std::string date)
	{
		return do_setEndDate(date);
	}

	
	void setCard(std::string cardNum)
	{
		return do_setCard(cardNum);
	}

	std::string getCardNum()const
	{
		return do_getCardNum();
	}

	unsigned long getBalance()const
	{
		return do_getBalance();
	}
	void setBalance(unsigned long sum)
	{
		return do_setBalance(sum);
	}
private:
	virtual unsigned long do_getBalance()const=0;
	virtual void do_setBalance(unsigned long) = 0;
	virtual void do_setCard(std::string) = 0;
	virtual std::string do_getCardNum()const = 0;
	virtual std::string  do_getStartDate() const = 0;
	virtual void do_setStartDate(std::string) = 0;
	virtual std::string do_getEndDate() const = 0;
	virtual void do_setEndDate(std::string date) = 0;

};

