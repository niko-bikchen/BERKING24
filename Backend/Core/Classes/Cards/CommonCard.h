#pragma once
#include "ICard.h"
#include <vector>

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
	std::vector<Transaction> _transactions;
	std::vector<Template> _templates;
	ModificationType _modificationType = UNCHANGED;

	void setModificationType(ModificationType) override;
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

	void addTemplate(Template) override;
	const std::vector<Template>& getTemplates() const override;
	const Template getTemplate(std::string) const override;

	void addTransaction(Transaction) override;
	const std::vector<Transaction>& getTransactions() const override;
	const Transaction getTransaction(std::string) const override;
	const std::vector<Transaction>& getTransactions(std::string, std::string) const override;

	ModificationType getModificationType() const override;
};
