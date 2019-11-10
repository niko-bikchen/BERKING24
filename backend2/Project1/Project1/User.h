#pragma once
#include "IUser.h"

class User :public IUser
{
public:
	User(std::string wT, std::string name, std::string password, std::string email,const std::list<std::string>& cards = {}) :
		_webToken(wT),_name(name),_password(password),_email(email),_cards(cards)
	{

	}
	
	~User() {}
private:
	User& operator=(const User&);
	User(const User&);

	std::list<std::string> _cards;
	std::string _webToken;
	std::string _name;
	std::string _password;
	std::string _email;
	
	class UserProxy;
	 
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

bool operator==(const IUser&, const IUser&);
