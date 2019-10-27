#pragma once
#pragma once
#include "IManager.h"
#include "CardManager.h"
#include "DepositManager.h"
#include "ClientManager.h"

class DBOperationsManager : public IManager
{
private:
	CardManager _cardManager;
	DepositManager _depositManager;
	ClientManager _clientManager;

	void update() override;
public:
	DBOperationsManager()
	{
	};

	~DBOperationsManager()
	{
	};

	const CardManager& getCardManager() const;
	const DepositManager& getDepositManager() const;
	const ClientManager& getClientManager() const;

	void setCardManager(const CardManager&);
	void setDepositManager(const DepositManager&);
	void setClientManager(const ClientManager&);
};
