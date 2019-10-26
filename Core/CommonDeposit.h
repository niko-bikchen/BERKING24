#pragma once
#include "IDeposit.h"

class CommonDeposit : public IDeposit
{
private:
	size_t _id;
	size_t _balance;
	size_t _originBalance;
	std::string _startDate;
	std::string _endDate;
public:
	CommonDeposit(int money, std::string stDate, std::string endDate);
	
	~CommonDeposit();
	
	std::string getStartDate() const override;
	void setStartDate(std::string) override;
	
	void setEndDate(std::string date) override;
	std::string getEndDate() const override;
};
