#include "SaveDepositProxy.h"
#include "OperationManager.h"



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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
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
#if DEBUG
			std::cout << "You are using an old object" << std::endl;
#endif
		}
	}
}




