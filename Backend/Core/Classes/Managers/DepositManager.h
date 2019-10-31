#pragma once
#include "IManager.h"
#include "IClient.h"
#include "CommonDeposit.h"
#include <vector>

class DepositManager : public IManager
{
private:
	struct Contract
	{
		size_t _id;
		IClient& _client;
		CommonDeposit _comD;
	};

	std::vector<Contract> _allContracts;
	std::vector<Contract> _modifiedContracts;

	const std::vector<Contract>& getContracts() const;
	void update() override;
public:
	DepositManager()
	{
	}

	~DepositManager()
	{
	};

	double getIncome() const;
	void changeIncome(double);

	double getLimit() const;
	void changeLimit(double) const;

	double getBalance(const CommonDeposit&, const IClient&) const;
	void setBalance(const CommonDeposit&, const IClient&, double);

	void endDeposit(const CommonDeposit&, const IClient&);

	const CommonDeposit& makeSaveDeposit(double, std::string, const IClient&);

	const Contract& getContract(const IClient&);
};
