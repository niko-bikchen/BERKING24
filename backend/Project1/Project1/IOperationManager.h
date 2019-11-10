#ifndef IOPERATIONMANAGER_H
#define IOPERATIONMANAGER_H
#include <string>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx\builder\stream\document.hpp>
#include <mongocxx\instance.hpp>

#include "IManager.h"
#include "DefferedICard.h"
#include "DefferedIDeposit.h"
#include "DefferedIUser.h"

class IOperationManager:IManager
{
public:
	IOperationManager() {};
	virtual ~IOperationManager() {};

	void addUser(const DefferedIUser& u)
	{
		return do_addUser(u);
	}

    DefferedIUser getUser(std::string email) 
	{
		return do_getUser(email);
	}
	
	DefferedISaveDeposit getSaveDeposit(std::string u)
	{
		return do_getSaveDeposit(u);
	}
	DefferedICard getCard( std::string num)
	{
		return do_getCard( num);
	}
	const mongocxx::database& getDB()
	{
		return do_getDB();
	}

	void addSaveDeposit(const DefferedISaveDeposit& d)
	{
		return do_addSaveDeposit(d);
	}
	void addCard(const DefferedICard& c)
	{
		return do_addCard(c);
	}
private:
	virtual void do_addSaveDeposit(const DefferedISaveDeposit&) = 0;
	virtual void do_addCard(const DefferedICard&) = 0;
	virtual const mongocxx::database& do_getDB() = 0;
	virtual void do_addUser(const DefferedIUser&) = 0;
	virtual DefferedIUser do_getUser(std::string)  = 0;
	virtual DefferedISaveDeposit do_getSaveDeposit(std::string) = 0;
	virtual DefferedICard do_getCard( std::string) = 0;

};
#endif