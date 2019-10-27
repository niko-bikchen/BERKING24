#pragma once
#include "IEntity.h"
#include <string>

class IDeposit : public IEntity
{
public:
	virtual ~IDeposit()= 0;
	virtual std::string  getStartDate() const = 0;
	virtual void setStartDate(std::string) = 0;
	
	virtual std::string getEndDate() const = 0;
	virtual void setEndDate(std::string date) = 0;
	
	virtual void endDeposit() const = 0;
};