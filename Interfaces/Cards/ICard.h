#pragma once
#include <string>
#include "IEntity.h"

class ICard : public IEntity
{
public:
	virtual ~ICard()
	{
	};

	virtual std::string getNumber() const = 0;

	virtual unsigned short getCVV() const = 0;

	virtual unsigned short getPIN() const = 0;
	virtual void setPIN(unsigned short) = 0;

	virtual std::string getName() const = 0;
	virtual void setName(std::string) = 0;

	virtual double getBalance() const = 0;
	virtual void setBalance(double) = 0;
};
