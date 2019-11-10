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
	static  IOperationManager* init(mongocxx::database& db)
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
	OperationManager(mongocxx::database& db) :_db(db) {}
	OperationManager(const OperationManager&);
	OperationManager& operator=(const OperationManager&);

	mongocxx::database& _db;
	static OperationManager* _op;


	void do_addSaveDeposit(const DefferedISaveDeposit&);
	void do_addCard(const DefferedICard&);
	void do_addUser(const DefferedIUser&);
	DefferedIUser do_getUser(std::string)const;
	DefferedISaveDeposit do_getSaveDeposit(std::string)const;
	DefferedICard do_getCard(std::string)const;
	void do_update();
	std::vector<DefferedIUser> do_getAllUsers()const;
	bool do_userExist(std::string email)const;
	bool do_cardExist(std::string num)const;
	bool do_depositExist(std::string num)const;
	virtual std::vector<DefferedISaveDeposit> do_getAllDeposits()const;
	virtual std::vector<DefferedICard> do_getAllCards()const;


	const mongocxx::database& do_getDB() const
	{
		return _db;
	}


};
bsoncxx::document::value  transactionToDocument(const ICard::Transaction& tr);
std::vector<ICard::Transaction>& documentToTransactions(const bsoncxx::v_noabi::types::b_array& ar);
#endif