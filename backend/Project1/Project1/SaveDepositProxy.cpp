#include "SaveDepositProxy.h"
#include "OperationManager.h"

unsigned long SaveDeposit::SaveDepositProxy::do_getBalance() const
{
	return _deposit._sum;
}

void SaveDeposit::SaveDepositProxy::do_setBalance(unsigned long c)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->depositExist(_deposit.getCardNum()));
	{
		DefferedISaveDeposit dep = op->getSaveDeposit(_deposit.getCardNum());
		if (*dep.operator->() == _deposit)
		{
			mongocxx::collection coll = op->getDB()["deposits"];
			coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
				make_document(kvp("balance", std::to_string(c))))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::ostream & SaveDeposit::SaveDepositProxy::do_print(std::ostream & out) const
{
	return _deposit.do_print(out);
}

void SaveDeposit::SaveDepositProxy::do_setCard(std::string num)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->depositExist(_deposit.getCardNum()));
	{
		DefferedISaveDeposit dep = op->getSaveDeposit(_deposit.getCardNum());
		if (*dep.operator->() == _deposit)
		{
			IOperationManager* op = OperationManager::getInstance();
			mongocxx::collection coll = op->getDB()["deposits"];
			coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
				make_document(kvp("card_number", num)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
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
	if (op->depositExist(_deposit.getCardNum()));
	{
		DefferedISaveDeposit dep = op->getSaveDeposit(_deposit.getCardNum());
		if (*dep.operator->() == _deposit)
		{
			IOperationManager* op = OperationManager::getInstance();
			mongocxx::collection coll = op->getDB()["deposits"];
			coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
				make_document(kvp("start_date", date)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

std::string SaveDeposit::SaveDepositProxy::do_getEndDate() const
{
	return _deposit._endDate;
}

void SaveDeposit::SaveDepositProxy::do_setEndDate(std::string date)
{
	IOperationManager* op = OperationManager::getInstance();
	if (op->depositExist(_deposit.getCardNum()));
	{
		DefferedISaveDeposit dep = op->getSaveDeposit(_deposit.getCardNum());
		if (*dep.operator->() == _deposit)
		{
			IOperationManager* op = OperationManager::getInstance();
			mongocxx::collection coll = op->getDB()["deposits"];
			coll.update_one(make_document(kvp("card_number", _deposit.getCardNum())), make_document(kvp("$set",
				make_document(kvp("end_date", date)))));
		}
		else
		{
			std::cout << "You are using an old object" << std::endl;
		}
	}
}

void SaveDeposit::SaveDepositProxy::do_endDeposit()
{
}


