#pragma once
#include <string>
#include <vector>
#include "ICard.h"
#include "IManager.h"
#include "IClient.h"

class CardManager : public IManager
{
private:
	struct CardPack
	{
		std::vector<ICard> cards;
		IClient& _client;
	};

	std::vector<CardPack> _allCards;
	std::vector<CardPack> _modifiedCards;
public:
	CardManager()
	{
	}

	~CardManager()
	{
	};

	void withdrawMoney(double, const IClient&);
	double checkMoney(const IClient&, std::string) const;

	void setComission(double);
	double getComission() const;

	const std::vector<CardPack>& getCardPacks() const;
	void setCardPacks(const std::vector<CardPack>&);

	const ICard& createCard(const IClient&, std::string);
	void deleteCard(const IClient&, std::string);
	const ICard& getCard(std::string, const IClient&) const;

	void makeTransaction(const IClient&, std::string, const IClient&, std::string, double);

	void update() override;
};
