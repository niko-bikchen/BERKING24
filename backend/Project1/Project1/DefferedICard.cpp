#include "DefferedICard.h"
#include "Card.h"

struct DefferedICard::CardRep
{
	ICard* _card;
	size_t _members;
	CardRep(std::string num, unsigned int cvv, unsigned int pin, std::string name,
		std::string endDate, std::vector<ICard::Transaction> transaction,
		std::vector<ICard::Transaction> templates, unsigned long balance) :_card(new Card(num,cvv,pin,name,
			                                             endDate,transaction,templates,balance)),_members(1)
	{
	}
};


DefferedICard::DefferedICard(std::string num, unsigned int cvv, unsigned int pin, std::string name,
	std::string endDate, std::vector<ICard::Transaction> transaction,
	std::vector<ICard::Transaction> templates, unsigned long balance):_cardRep(new CardRep(num,cvv,pin,name,
		                                                                endDate,transaction,templates,balance))
{
}

DefferedICard::DefferedICard(const DefferedICard & dc):_cardRep(dc._cardRep)
{
	++_cardRep->_members;
}

DefferedICard::~DefferedICard()
{
	if (--_cardRep->_members == 0)
	{
		delete _cardRep->_card;
	}
		
}

DefferedICard & DefferedICard::operator=(const DefferedICard & d)
{
	if (this->_cardRep == d._cardRep)
	{
		return *this;
	}
	if (--_cardRep->_members == 0)
	{
		delete _cardRep;
	}
	_cardRep = d._cardRep;
	++_cardRep->_members;
	return *this;

}

ICard * DefferedICard::operator->() const
{
	return _cardRep->_card;
}


