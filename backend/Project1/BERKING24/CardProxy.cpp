#include "CardProxy.h"
#include "OperationManager.h"

void Card::CardProxy::do_setDate(std::string s)
{

	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(
				kvp("$set", make_document(kvp("date_end", s)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}


}

std::string Card::CardProxy::do_getDate() const
{
	return _card._endDate;
}

void Card::CardProxy::do_setNumber(std::string num)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("number_card", num)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string Card::CardProxy::do_getNumber() const
{
	return _card._number;
}

unsigned int Card::CardProxy::do_getCVV() const
{
	return _card._cvv;
}

void Card::CardProxy::do_setCVV(unsigned int num)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("cvv", std::to_string(num))))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

unsigned int Card::CardProxy::do_getPIN() const
{
	return _card._pin;
}

void Card::CardProxy::do_setPIN(unsigned int num)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("pin", std::to_string(num))))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string Card::CardProxy::do_getName() const
{
	return _card._name;
}

void Card::CardProxy::do_setName(std::string name)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("name", name)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

unsigned long Card::CardProxy::do_getBalance() const
{
	return _card._balance;
}

void Card::CardProxy::do_setBalance(unsigned long money)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("card_balance", std::to_string(money))))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

const std::vector<Card::Transaction>& Card::CardProxy::do_getTransactions() const
{
	return _card._transactions;
}


void Card::CardProxy::do_setTransactions(std::vector<Transaction>& tr)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			auto array_builder = bsoncxx::builder::basic::array{};
			std::vector<Transaction>::iterator i;
			for (i = tr.begin(); i != tr.end(); ++i)
			{
				array_builder.append(transactionToDocument(*i));
			}
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("transactions", array_builder)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

const std::vector<Card::Transaction>& Card::CardProxy::do_getTemplates() const
{
	return _card._templates;
}

void Card::CardProxy::do_setTemplates(std::vector<Transaction>& tm)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			auto array_builder = bsoncxx::builder::basic::array{};
			std::vector<Transaction>::iterator i;
			for (i = tm.begin(); i != tm.end(); ++i)
			{
				array_builder.append(transactionToDocument(*i));
			}

			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("templates", array_builder)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

void Card::CardProxy::do_addTemplate(const Transaction& tr)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			auto array_builder = bsoncxx::builder::basic::array{};
			std::vector<Transaction>::iterator i;
			std::vector<Transaction> ar = _card.do_getTemplates();
			for (i = ar.begin(); i != ar.end(); ++i)
			{
				array_builder.append(transactionToDocument(*i));
			}
			array_builder.append(transactionToDocument(tr));
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("templates", array_builder)))));

		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

void Card::CardProxy::do_addTransaction(const Transaction& tr)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->cardExist(_card.getNumber()))
	{
		DefferedICard c = op->getCard(_card.getNumber());
		if (*c.operator->() == _card)
		{
			auto array_builder = bsoncxx::builder::basic::array{};
			std::vector<Transaction>::iterator i;
			std::vector<Transaction> ar = _card.do_getTransactions();
			for (i = ar.begin(); i != ar.end(); ++i)
			{

				array_builder.append(transactionToDocument(*i));
			}
			array_builder.append(transactionToDocument(tr));
			mongocxx::collection coll = op->getDB()["cards"];
			coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
				make_document(kvp("transactions", array_builder)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::ostream& Card::CardProxy::do_print(std::ostream& os) const
{
	return _card.do_print(os);
}