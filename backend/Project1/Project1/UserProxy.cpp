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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
}




