#ifndef OPERATIONMANAGER_H
#define OPERATIONMANAGER_H
#include "IOperationManager.h"


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_document;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::make_array;

class OperationManager :public IOperationManager
{
public:
	~OperationManager() 
	{
	}
	static  IOperationManager* getInstance(mongocxx::database& db)
	{
		if (!_op)
		{
			_op = new OperationManager(db);
		}
		return _op;
	}

	static  IOperationManager* getInstance()
	{
		if (!_op)
		{
			return NULL;
		}
		return _op;
	}



private:
	OperationManager(mongocxx::database& db):_db(db){}
	OperationManager(const OperationManager&);
	OperationManager& operator=(const OperationManager&);
	
	mongocxx::database& _db;
	static OperationManager * _op;
	
	
	void do_addSaveDeposit(const DefferedISaveDeposit&);
	void do_addCard(const DefferedICard&);
	void do_addUser(const DefferedIUser&);
	DefferedIUser do_getUser(std::string);
	DefferedISaveDeposit do_getSaveDeposit(std::string);
	DefferedICard do_getCard(std::string);
	void do_update();
	
	
	const mongocxx::database& do_getDB() 
	{
		return _db;
	}
	
	
};
bsoncxx::document::value  transactionToDocument(const ICard::Transaction& tr);
std::vector<ICard::Transaction>& documentToTransactions(const bsoncxx::v_noabi::types::b_array& ar);
#endif