#pragma once
#include <string>
#include "IManager.h"
#include "IClient.h"
#include "CardManager.h"
#include "DepositManager.h"

class ClientManager : public IManager
{
private:
	struct Transaction
	{
		size_t _id;
		std::string _date;
		std::string _senderCardNum;
		std::string _receiverCardNum;
		size_t _amountOfMoney;
		std::string _description;
	};

	std::vector<IClient> _clients;
public:
	ClientManager()
	{
	}

	~ClientManager()
	{
	}

	void addClient(std::string, std::string, std::string, std::string, std::string, const CardManager&,
	               const DepositManager&);
	const IClient& getClient(std::string) const;
	void deleteClient(std::string);

	void makeTemplate(std::string, std::string, unsigned int, std::string);
	const std::vector<Transaction>& getTemplates() const;
	const std::vector<Transaction>& getTemplate(std::string, std::string) const;

	const std::vector<Transaction>& getTransaction(std::string, std::string) const;
	const std::vector<Transaction>& getTransaction(std::string, unsigned int) const;
	const std::vector<Transaction>& getTransactions() const;

	void update() override;
};
