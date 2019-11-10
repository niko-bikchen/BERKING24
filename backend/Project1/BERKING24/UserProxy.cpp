#include "UserProxy.h"

#include "OperationManager.h"



void User::UserProxy::do_addCard(std::string num)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->userExist(_user.getEmail()));
	{
		DefferedIUser c = op->getUser(_user.getEmail());
		if (*c.operator->() == _user)
		{
			mongocxx::collection coll = op->getDB()["users"];

			std::list<std::string>::iterator i;
			auto array_builder = bsoncxx::builder::basic::array{};
			std::list<std::string> ar = _user.getCards();
			for (i = ar.begin(); i != ar.end(); ++i)
			{
				array_builder.append(*i);
			}
			array_builder.append(num);
			coll.update_one(make_document(kvp("email", _user.getEmail())), make_document(kvp("$set",
				make_document(kvp("cards", array_builder)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

void User::UserProxy::do_deleteCard(std::string)
{
}

const std::list<std::string>& User::UserProxy::do_getCards() const
{
	return _user._cards;
}

void User::UserProxy::do_setCards(std::list<std::string>& cards)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->userExist(_user.getEmail()));
	{
		DefferedIUser c = op->getUser(_user.getEmail());
		if (*c.operator->() == _user)
		{
			mongocxx::collection coll = op->getDB()["users"];

			std::list<std::string>::iterator i;
			auto array_builder = bsoncxx::builder::basic::array{};
			for (i = cards.begin(); i != cards.end(); ++i)
			{
				array_builder.bsoncxx::builder::basic::sub_array::append(*i);
			}

			coll.update_one(make_document(kvp("email", _user.getEmail())), make_document(kvp("$set",
				make_document(kvp("cards", array_builder)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string User::UserProxy::do_getWebToken() const
{
	return _user._webToken;
}

void User::UserProxy::do_setWebToken(std::string web)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->userExist(_user.getEmail()));
	{
		DefferedIUser c = op->getUser(_user.getEmail());
		if (*c.operator->() == _user)
		{
			mongocxx::collection coll = op->getDB()["users"];
			coll.update_one(make_document(kvp("email", _user.getEmail())), make_document(kvp("$set",
				make_document(kvp("webtoken", web)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string User::UserProxy::do_getName() const
{
	return _user._name;
}

void User::UserProxy::do_setName(std::string name)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->userExist(_user.getEmail()));
	{
		DefferedIUser c = op->getUser(_user.getEmail());
		if (*c.operator->() == _user)
		{
			IOperationManager* op = OperationManager::getInstance();
			mongocxx::collection coll = op->getDB()["users"];
			coll.update_one(make_document(kvp("email", _user.getEmail())), make_document(kvp("$set",
				make_document(kvp("name", name)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string User::UserProxy::do_getPassword() const
{
	return _user._password;
}

void User::UserProxy::do_setPassword(std::string pass)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->userExist(_user.getEmail()));
	{
		DefferedIUser c = op->getUser(_user.getEmail());
		if (*c.operator->() == _user)
		{
			IOperationManager* op = OperationManager::getInstance();
			mongocxx::collection coll = op->getDB()["users"];
			coll.update_one(make_document(kvp("email", _user.getEmail())), make_document(kvp("$set",
				make_document(kvp("password", pass)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string User::UserProxy::do_getEmail() const
{
	return _user._email;
}

void User::UserProxy::do_setEmail(std::string em)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->userExist(_user.getEmail()));
	{
		DefferedIUser c = op->getUser(_user.getEmail());
		if (*c.operator->() == _user)
		{
			IOperationManager* op = OperationManager::getInstance();
			mongocxx::collection coll = op->getDB()["users"];
			coll.update_one(make_document(kvp("email", _user.getEmail())), make_document(kvp("$set",
				make_document(kvp("email", em)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}


void User::UserProxy::do_endDeposit(const ISaveDeposit&)
{
}

std::ostream& User::UserProxy::do_print(std::ostream& os) const
{
	return _user.do_print(os);
}
