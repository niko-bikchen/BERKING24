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
#include "DepositFunctor.h"
class IOperationManager :IManager
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
	DefferedICard getCard(std::string num)
	{
		return do_getCard(num);
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
	std::vector<DefferedIUser> getAllUsers()
	{
		return do_getAllUsers();
	}
	std::vector<DefferedISaveDeposit> getAllDeposits()
	{
		return do_getAllDeposits();
	}
	std::vector<DefferedICard> getAllCards()
	{
		return do_getAllCards();
	}
	bool userExist(std::string email)const
	{
		return do_userExist(email);
	}
	bool cardExist(std::string num)const
	{
		return do_cardExist(num);
	}
	bool depositExist(std::string num)const
	{
		return do_depositExist(num);
	}
	void deleteCard(std::string num)
	{
		return do_deleteCard(num);
	}
	void deleteDeposit(std::string num,const DepositFunctor& func)
	{
		return do_deleteDeposit(num,func);
	}
	std::vector<DefferedICard> getAllUsersCards(std::string email)
	{
		return do_getAllUsersCards(email);
	}
private:
	virtual std::vector<DefferedICard> do_getAllUsersCards(std::string) = 0;
	virtual void do_deleteDeposit(std::string ,const DepositFunctor&) = 0;
	virtual void do_deleteCard(std::string) = 0;
	virtual std::vector<DefferedISaveDeposit> do_getAllDeposits()const = 0;
	virtual std::vector<DefferedICard> do_getAllCards()const = 0;
	virtual void do_addSaveDeposit(const DefferedISaveDeposit&) = 0;
	virtual void do_addCard(const DefferedICard&) = 0;
	virtual const mongocxx::database& do_getDB()const = 0;
	virtual void do_addUser(const DefferedIUser&) = 0;
	virtual DefferedIUser do_getUser(std::string)const = 0;
	virtual DefferedISaveDeposit do_getSaveDeposit(std::string)const = 0;
	virtual DefferedICard do_getCard(std::string)const = 0;
	virtual std::vector<DefferedIUser> do_getAllUsers()const = 0;
	virtual bool do_userExist(std::string email)const = 0;
	virtual bool do_cardExist(std::string num)const = 0;
	virtual bool do_depositExist(std::string num)const = 0;


};
#endif