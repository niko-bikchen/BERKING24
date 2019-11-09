#include "CardProxy.h"
#include "OperationManager.h"

void Card::CardProxy::do_setDate(std::string s)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", _card.getNumber())), bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
		bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("date_end", s)))));

}

std::string Card::CardProxy::do_getDate() const
{
	return _card._endDate;
}

void Card::CardProxy::do_setNumber(std::string num)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", _card.getNumber())), bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
		bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", num)))));
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
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", _card.getNumber())), bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
		bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("cvv", std::to_string(num))))));
}

unsigned int Card::CardProxy::do_getPIN() const
{
	return _card._pin;
}

void Card::CardProxy::do_setPIN(unsigned int num)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", _card.getNumber())), bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
		bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("pin", std::to_string(num))))));
}

std::string Card::CardProxy::do_getName() const
{
	return _card._name;
}

void Card::CardProxy::do_setName(std::string name)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", _card.getNumber())), bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
		bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("name", name)))));
}

unsigned long Card::CardProxy::do_getBalance() const
{
	return _card._balance;
}

void Card::CardProxy::do_setBalance(unsigned long money)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", _card.getNumber())), bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
		bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("card_balance", std::to_string(money))))));
}

const std::vector<Card::Transaction>& Card::CardProxy::do_getTransactions() const
{
	return _card._transactions;
}

void Card::CardProxy::do_setTransactions(std::vector<Transaction>& tr)
{

	auto array_builder = bsoncxx::builder::basic::array{};
	std::vector<Transaction>::iterator i ;
	for (i = tr.begin(); i != tr.end(); ++i)
	{
		array_builder.append(transactionToDocument(*i));
	}

	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
		make_document(kvp("transactions", array_builder)))));
}

const std::vector<Card::Transaction>& Card::CardProxy::do_getTemplates() const
{
	return _card._templates;
}

void Card::CardProxy::do_setTemplates(std::vector<Transaction>& tm)
{
	auto array_builder = bsoncxx::builder::basic::array{};
	std::vector<Transaction>::iterator i;
	for (i = tm.begin(); i != tm.end(); ++i)
	{
		array_builder.append(transactionToDocument(*i));
	}

	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
		make_document(kvp("templates", array_builder)))));
}

void Card::CardProxy::do_addTemplate(const Transaction & tr)
{
	auto array_builder = bsoncxx::builder::basic::array{};
	std::vector<Transaction>::iterator i;
	std::vector<Transaction> ar = _card.do_getTemplates();
	for (i = ar.begin(); i != ar.end(); ++i)
	{
		array_builder.append(transactionToDocument(*i));
	}

	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
		make_document(kvp("templates", array_builder)))));
}

void Card::CardProxy::do_addTransaction(const Transaction &tr)
{
	auto array_builder = bsoncxx::builder::basic::array{};
	std::vector<Transaction>::iterator i;
	std::vector<Transaction> ar = _card.do_getTransactions();
	for (i = ar.begin(); i != ar.end(); ++i)
	{
		
		array_builder.append(transactionToDocument(*i));
	}

	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["cards"];
	coll.update_one(make_document(kvp("number_card", _card.getNumber())), make_document(kvp("$set",
		make_document(kvp("transactions", array_builder)))));
}

std::ostream & Card::CardProxy::do_print(std::ostream & os) const
{
	return _card.do_print(os);
}
