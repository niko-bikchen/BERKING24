#pragma once
#include "ICard.h"
#include "IManager.h"
#include "IClient.h"
#include <string>
#include <vector>

class ICardManager : public IManager
{
public:
	struct CardPack
	{
	};

	virtual ~ICardManager()
	{
	};

	void takeMoney(double m, const IClient& u)
	{
		return do_takeMoney(m, u);
	}

	double checkMoney(const IClient& u, std::string num) const
	{
		return do_checkMoney(u, num);
	}

	void setComission(double coef)
	{
		return do_setComission(coef);
	}

	double getComission() const
	{
		return do_getComission();
	}

	const std::vector<CardPack>& getCardPacks() const
	{
		return do_getCardPacks();
	}

	void setCardPacks(const std::vector<CardPack>& c)
	{
		return do_setCardPacks(c);
	}

	const ICard& makeCard(const IClient& u, std::string name)
	{
		return do_makeCard(u, name);
	}

	void deleteCard(const IClient& u, std::string name)
	{
		return do_deleteCard(u, name);
	}

	void throwMoney(const IClient& uSender, std::string numSender, const IClient& uReciever, std::string numReciever,
	                double sum)
	{
		return do_throwMoney(uSender, numSender, uReciever, numReciever, sum);
	}

	const ICard& getCard(std::string num, const IClient& u) const
	{
		return do_getCard(num, u);
	}

private:
	virtual void do_takeMoney(double, const IClient&) = 0;
	virtual double do_checkMoney(const IClient&, std::string) const = 0;
	virtual void do_setComission(double) = 0;
	virtual double do_getComission() const = 0;
	virtual const std::vector<CardPack>& do_getCardPacks() const = 0;
	virtual void do_setCardPacks(const std::vector<CardPack>&) = 0;
	virtual const ICard& do_makeCard(const IClient&, std::string) = 0;
	virtual void do_deleteCard(const IClient&, std::string) = 0;
	virtual void do_throwMoney(const IClient&, std::string, const IClient&, std::string, double) = 0;
	virtual const ICard& do_getCard(std::string, const IClient&) const = 0;
};
