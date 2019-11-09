#include "SaveDepositProxy.h"
#include "OperationManager.h"

unsigned long SaveDeposit::SaveDepositProxy::do_getBalance() const
{
	return _deposit._sum;
}

void SaveDeposit::SaveDepositProxy::do_setBalance(unsigned long c)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["deposits"];
	coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
		make_document(kvp("balance", std::to_string(c))))));
}

std::ostream & SaveDeposit::SaveDepositProxy::do_print(std::ostream & out) const
{
	return _deposit.do_print(out);
}

void SaveDeposit::SaveDepositProxy::do_setCard(std::string num)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["deposits"];
	coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
		make_document(kvp("card_number", num)))));
}

std::string SaveDeposit::SaveDepositProxy::do_getCardNum() const
{
	return _deposit._cardNum;
}

std::string SaveDeposit::SaveDepositProxy::do_getStartDate() const
{
	return _deposit._startDate;
}

void SaveDeposit::SaveDepositProxy::do_setStartDate(std::string date)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["deposits"];
	coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
		make_document(kvp("start_date", date)))));
}

std::string SaveDeposit::SaveDepositProxy::do_getEndDate() const
{
	return _deposit._endDate;
}

void SaveDeposit::SaveDepositProxy::do_setEndDate(std::string date)
{
	IOperationManager* op = OperationManager::getInstance();
	mongocxx::collection coll = op->getDB()["deposits"];
	coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
		make_document(kvp("end_date", date)))));
}

void SaveDeposit::SaveDepositProxy::do_endDeposit()
{
}