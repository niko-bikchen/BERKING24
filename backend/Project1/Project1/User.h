#pragma once
#include "DefferedIUser.h"

class User :public IUser
{
public:
	friend  DefferedIUser::DefferedIUser(std::string, std::string, std::string, std::string, const std::list<std::string>&);
	
	~User() {}
private:
	User(std::string wT, std::string name, std::string password, std::string email, const std::list<std::string>& cards = {}) :
		_webToken(wT), _name(name), _password(password), _email(email), _cards(cards)
	{

	}


	User& operator=(const User&);
	User(const User&);

	std::list<std::string> _cards;
	std::string _webToken;
	std::string _name;
	std::string _password;
	std::string _email;
	
	class UserProxy;
	 
	 void do_addCard(std::string);
	 bool do_hasCard(std::string);
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
	 std::ostream& do_print(std::ostream&) const;
	
};

bool operator==(const IUser&, const IUser&);
