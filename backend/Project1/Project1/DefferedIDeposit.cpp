#include "DefferedIDeposit.h"
#include "SaveDeposit.h"

struct DefferedISaveDeposit::DepositRep
{
	ISaveDeposit* _deposit;
	size_t _members;
	DepositRep(std::string cN, std::string sD, std::string eD, unsigned long sum) :
		_deposit(new SaveDeposit(cN, sD, eD, sum)),_members(1)
	{
	}
};


DefferedISaveDeposit::DefferedISaveDeposit(std::string cN, std::string sD, std::string eD, unsigned long sum):
	_depositRep(new DepositRep(cN,sD,eD,sum))
{
}

DefferedISaveDeposit::DefferedISaveDeposit(const DefferedISaveDeposit &d):_depositRep(d._depositRep)
{
	++_depositRep->_members;
}

DefferedISaveDeposit::~DefferedISaveDeposit()
{
	if (--_depositRep->_members == 0)
	{
		delete _depositRep->_deposit;
	}
}

DefferedISaveDeposit & DefferedISaveDeposit::operator=(const DefferedISaveDeposit & d)
{
	if (this->_depositRep == d._depositRep)
	{
		return *this;
	}
	if (--_depositRep->_members == 0)
	{
		delete _depositRep;
	}
	_depositRep = d._depositRep;
	++_depositRep->_members;
	return *this;
}

ISaveDeposit * DefferedISaveDeposit::operator->() const
{
	return _depositRep->_deposit;
}
