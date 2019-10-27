#pragma once
#include "ICard.h"

class CommonCard : public ICard
{
private:
	size_t _id;
	std::string _number;
	unsigned short _cvv;
	unsigned short _pin;
	std::string _name;
	std::string _endDate;
	std::string _balance;
	Status _status;

	void setStatus(Status) override;
public:
	CommonCard(std::string number, unsigned short cvv, unsigned short pin)
	{
	}

	~CommonCard()
	{
	}

	size_t getId() const override;

	std::string getNumber() const override;

	unsigned short getCVV() const override;

	unsigned short getPIN() const override;
	void setPIN(unsigned short) override;

	std::string getName() const override;
	void setName(std::string) override;

	double getBalance() const override;
	void setBalance(double) override;

	Status getStatus() const override;
};
