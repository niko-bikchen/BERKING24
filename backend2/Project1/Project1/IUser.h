#pragma once
#include "IEntity.h"
#include <list>
#include "ICard.h"
#include "ISaveDeposit.h"
class IUser :public IEntity
{
public:


	IUser() {};
	virtual ~IUser() {};

	void addCard(std::string name)
	{
		return do_addCard(name);
	}

	void deleteCard(std::string cardNum)
	{
		return do_deleteCard(cardNum);
	}
	
	const std::list<std::string>& getCards() const
	{
		return do_getCards();
	}

	void setCards(std::list<std::string>& cards)
	{
		return do_setCards(cards);
	}

	std::string getWebToken() const
	{
		return do_getWebToken();
	}
	void setWebToken(std::string token)
	{
		return do_setWebToken(token);
	}
	std::string getName()const
	{
		return do_getName();
	}
	void setName(std::string s)
	{
		return do_setName(s);
	}
	std::string getPassword() const
	{
		return do_getPassword();
	}
	void setPassword(std::string password)
	{
		return do_setPassword(password);
	}
	std::string getEmail() const
	{
		return do_getEmail();
	}
	void setEmail(std::string em)
	{
		return do_setEmail(em);
	}

	void endDeposit(const ISaveDeposit& dp)
	{
		return do_endDeposit(dp);
	}

	

private:
	virtual void do_addCard(std::string) = 0;
	virtual void do_deleteCard(std::string) = 0;
	virtual const std::list<std::string>& do_getCards()const = 0;
	virtual void do_setCards(std::list<std::string>&) = 0;
	virtual std::string do_getWebToken() const = 0;
	virtual void do_setWebToken(std::string) = 0;
	virtual std::string do_getName()const = 0;
	virtual void do_setName(std::string) = 0;
	virtual std::string do_getPassword() const = 0;
	virtual void do_setPassword(std::string) = 0;
	virtual std::string do_getEmail() const = 0;
	virtual void do_setEmail(std::string) = 0;
	virtual void do_endDeposit(const ISaveDeposit&) = 0;

};
