#include "UserProxy.h"
#include "User.h"

void User::do_addCard(std::string tm)
{
	_cards.insert(_cards.begin(), 1, tm);
	UserProxy uP = UserProxy(*this);
	uP.do_addCard(tm);
}

void User::do_deleteCard(std::string cardNum)
{
	std::list<std::string>::iterator i;
	for ( i=_cards.begin(); i!=_cards.end(); ++i)
	{
		if (*i != cardNum && i ==_cards.end())
		{
			return;
		}
		
	}

	_cards.remove(cardNum);

}

 const std::list<std::string>& User::do_getCards() const
{
	return _cards;
}

void User::do_setCards(std::list<std::string>& c)
{
	_cards = c;
	UserProxy uP = UserProxy(*this);
	uP.do_setCards(c);
}

std::string User::do_getWebToken() const
{
	return _webToken;
}

void User::do_setWebToken(std::string wT)
{
		_webToken = wT;
		UserProxy uP = UserProxy(*this);
		uP.do_setWebToken(wT);
}

std::string User::do_getName() const
{
	return _name;
}

void User::do_setName(std::string name)
{
	_name = name;
	UserProxy uP = UserProxy(*this);
	uP.do_setName(name);
}

std::string User::do_getPassword() const
{
	return _password;
}

void User::do_setPassword(std::string pass)
{
	_password = pass;
	UserProxy uP = UserProxy(*this);
	uP.do_setPassword(pass);
}

std::string User::do_getEmail() const
{
	return _email;
}

void User::do_setEmail(std::string em)
{
	UserProxy uP = UserProxy(*this);
	uP.do_setEmail(em);
	_email = em;
}

//TODO BD
void User::do_endDeposit(const ISaveDeposit &)
{
}

std::ostream & User::do_print(std::ostream & os) const
{
	os << "Name :" << this->do_getName() << '\n'
		<< "Email :" << this->do_getEmail() << '\n'
		<< "Password :" << this->getPassword() << '\n';
	return os;
}

