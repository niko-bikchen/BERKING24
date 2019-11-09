#pragma once
#include "User.h"

class User::UserProxy :public IUser
{
	friend class User;
private:
	User& _user;

	UserProxy(User& c) :_user(c)
	{

	}
public:
	void do_addCard(std::string);
	void do_deleteCard(std::string);
	const std::list<std::string>& do_getCards()const;
	void do_setCards(std::list<std::string>&);
	std::string do_getWebToken() const;
	void do_setWebToken(std::string);
	std::string do_getName()const;
	void do_setName(std::string);
	std::string do_getPassword() const;
	void do_setPassword(std::string);
	std::string do_getEmail() const;
	void do_setEmail(std::string);
	void do_endDeposit(const ISaveDeposit&);
	std::ostream& do_print(std::ostream&) const;
};
