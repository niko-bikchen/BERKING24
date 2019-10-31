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

	void update() override;
	const std::vector<CardPack>& getCardPacks() const;
public:
	CardManager()
	{
	}

	~CardManager()
	{
	};

	void withdrawMoney(const IClient&, std::string, double);
	double checkMoney(const IClient&, std::string) const;

	const ICard& createCard(const IClient&, std::string, unsigned short, unsigned short);
	void deleteCard(const IClient&, std::string);
	
	const ICard& getCard(const IClient&, std::string) const;
	const std::vector<ICard> getCards(const IClient&) const;

	void makeTransaction(const IClient&, std::string, const IClient&, std::string, double);

	void createTemplate(std::string, std::string, unsigned int, std::string);
};
