#pragma once
#include "User.h"

class User::UserProxy 
{
	friend class User;
private:
	User& _user;

	UserProxy(User& c) :_user(c)
	{

	}


	void do_addCard(std::string);
	void do_setCards(std::list<std::string>&);
	void do_setWebToken(std::string);
	void do_setName(std::string);
	void do_setPassword(std::string);
	void do_setEmail(std::string);
public:
	
};

