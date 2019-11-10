#pragma once
#include "ICard.h"

class DefferedICard
{
private:
	struct CardRep;
	CardRep* _cardRep;

	ICard& operator*()const;
public:
	DefferedICard(std::string num, unsigned int cvv, unsigned int pin, std::string name, std::string endDate,
		std::vector<ICard::Transaction> transaction = {}, std::vector<ICard::Transaction> templates = {}, unsigned long balance = 0);
	DefferedICard(const DefferedICard&);
	~DefferedICard();
	DefferedICard& operator=(const DefferedICard&);



	ICard* operator->()const;


};
