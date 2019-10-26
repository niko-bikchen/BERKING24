#pragma once
#include "IManager.h"
#include "IUniversalDeposit.h"
#include "IClient.h"
#include <string>
#include "../Core/SaveDeposit.h"


class IDepositManager : public IManager
{
public:

	virtual ~IDepositManager()
	{
	};

	double getIncome() const
	{
		return do_getIncome();
	}

	void changeIncome(double inc)
	{
		return do_changeIncome(inc);
	}

	double getLimit() const
	{
		return do_getLimit();
	}

	void changeLimit(double lim)
	{
		return do_changeLimit(lim);
	}

	double getBalance(const SaveDeposit& dp, const IClient& u) const
	{
		return do_getBalance(dp, u);
	}

	void setBalance(const SaveDeposit& dp, const IClient& u, double money)
	{
		return do_setBalance(dp, u, money);
	}

	void endDeposit(const SaveDeposit& dp, const IClient& u)
	{
		return do_endDeposit(dp, u);
	}

	const SaveDeposit& makeSaveDeposit(double money, std::string endDate);
private:
	virtual double do_getIncome() const = 0;
	virtual void do_changeIncome(double) = 0;
	virtual double do_getLimit() const = 0;
	virtual void do_changeLimit(double) const = 0;
	virtual double do_getBalance(const SaveDeposit&, const IClient&) const = 0;
	virtual void do_setBalance(const SaveDeposit&, const IClient&, double) = 0;
	virtual void do_endDeposit(const SaveDeposit&, const IClient&) = 0;
};
