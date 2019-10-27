#pragma once
#include <string>
#include "IManager.h"
#include "IClient.h"
#include "CardManager.h"
#include "DepositManager.h"

class ClientManager : public IManager
{
private:
	std::vector<IClient> _clients;
	std::vector<IClient> _modifiedClients;

	void update() override;
public:
	ClientManager()
	{
	}

	~ClientManager()
	{
	}

	void addClient(std::string, std::string, std::string);
	const IClient& getClient(std::string) const;
	void deleteClient(std::string);
};
