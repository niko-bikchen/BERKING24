#pragma once
#include <string>
#include "IEntity.h"
#include <vector>

class ICard : public IEntity
{
public:
	virtual ~ICard()
	{
	};

	struct Transaction
	{
		size_t _id;
		std::string _date;
		std::string _receiverCardNum;
		size_t _amountOfMoney;
		std::string _description;
	};

	struct Template
	{
		size_t _id;
		std::string _receiverCardNum;
		size_t _amountOfMoney;
		std::string _description;
	};

	virtual std::string getNumber() const = 0;

	virtual unsigned short getCVV() const = 0;

	virtual unsigned short getPIN() const = 0;
	virtual void setPIN(unsigned short) = 0;

	virtual std::string getName() const = 0;
	virtual void setName(std::string) = 0;

	virtual double getBalance() const = 0;
	virtual void setBalance(double) = 0;

	virtual void addTemplate(Template) = 0;
	virtual const std::vector<Template>& getTemplates() const = 0;
	virtual const Template getTemplate(std::string) const = 0;

	virtual void addTransaction(Transaction) = 0;
	virtual const std::vector<Transaction>& getTransactions(std::string, std::string) const = 0;
	virtual const Transaction getTransaction(std::string) const = 0;
	virtual const std::vector<Transaction>& getTransactions() const = 0;
};
