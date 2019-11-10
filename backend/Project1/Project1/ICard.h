#pragma once
#include "IEntity.h"
#include <string>
#include <vector>

class ICard :public IEntity
{
public:
	ICard() {};
	virtual ~ICard() {};

	struct Transaction;
	

	std::string getNumber() const
	{
		return do_getNumber();
	}

	void setNumber(std::string num)
	{
		return do_setNumber(num);
	}

	unsigned int getCVV() const
	{
		return do_getCVV();
	}

	void setCVV(unsigned int num)
	{
		return do_setCVV(num);
	}

	unsigned int getPIN() const
	{
		return do_getPIN();
	}

	void setPIN(unsigned int num)
	{
		return do_setPIN(num);
	}

	std::string getName() const
	{
		return do_getName();
	}

	void setName(std::string name)
	{
		return do_setName(name);
	}

	double getBalance() const
	{
		return do_getBalance();
	}

	void setBalance(unsigned long num)
	{
		return do_setBalance(num);
	}


	const std::vector<Transaction>& getTransactions()const
	{
		return do_getTransactions();
	}
	void setTransactions( std::vector<Transaction>& tr)
	{
		return do_setTransactions(tr);
	}
	const std::vector<Transaction>& getTemplates()const
	{
		return do_getTemplates();
	}
	void setTemplates( std::vector<Transaction>& tm)
	{
		return do_setTemplates(tm);
	}

	void addTemplate(const Transaction& tm)
	{
		return do_addTemplate(tm);
	}
	void addTransaction(const Transaction&tr)
	{
		return do_addTransaction(tr);
	}

	std::string getDate() const
	{
		return do_getDate();
	}
	void setDate(std::string st)
	{
		return do_setDate(st);
	}
	

	

private:
	virtual void do_setDate(std::string) = 0;
	virtual std::string do_getDate()const = 0;
	virtual void do_setNumber(std::string) = 0;
	virtual std::string do_getNumber()const = 0;
	virtual unsigned int do_getCVV()const = 0;
	virtual void do_setCVV(unsigned int) = 0;
	virtual unsigned int do_getPIN() const = 0;
	virtual void  do_setPIN(unsigned int) = 0;
	virtual std::string do_getName()const = 0;
	virtual void do_setName(std::string) = 0;
	virtual unsigned long do_getBalance() const = 0;
	virtual void do_setBalance(unsigned long) = 0;
	virtual const std::vector<Transaction>& do_getTransactions()const = 0;
	virtual void do_setTransactions( std::vector<Transaction>&) = 0;
	virtual const std::vector<Transaction>& do_getTemplates()const = 0;
	virtual void do_setTemplates( std::vector<Transaction>&) = 0;
	virtual void do_addTemplate(const Transaction&) = 0;
	virtual void do_addTransaction(const Transaction&) = 0;


};

struct ICard::Transaction
{
private:
	std::string _date;
	std::string _senderCardNum;
	std::string _recieverCardNum;
	unsigned long _sum;
	std::string _description;
public:
	Transaction(std::string date, std::string scn, std::string rcn, unsigned long sum, std::string desc) :
		_date(date), _senderCardNum(scn), _recieverCardNum(rcn), _sum(sum), _description(desc)
	{

	}
	~Transaction() {}
	
	std::string getDate() const
	{
		return _date;
	}

	void setDate(std::string d)
	{
		_date = d;
	}

	std::string getSenderCardNum() const
	{
		return _senderCardNum;
	}

	void setSenderCardNum(std::string scn)
	{
		_senderCardNum = scn;
	}

	std::string getrecieverCardNum() const
	{
		return _recieverCardNum;
	}

	void setrecieverCardNum(std::string rcn)
	{
		_recieverCardNum = rcn;
	}

	std::string getDescription() const
	{
		return _description;
	}

	void setDescription(std::string descr)
	{
		_description = descr;
	}

	unsigned long getSum() const
	{
		return _sum;
	}

	void setSum(unsigned long sum)
	{
		_sum = sum;
	}



};

