#pragma once
#include "ISaveDeposit.h"
class DefferedISaveDeposit
{
private:
	struct DepositRep;
	DepositRep* _depositRep;

	ISaveDeposit& operator*()const;
public:
	DefferedISaveDeposit(std::string cN, std::string sD, std::string eD, unsigned long sum);
	DefferedISaveDeposit(const DefferedISaveDeposit&);
	~DefferedISaveDeposit();
	DefferedISaveDeposit& operator=(const DefferedISaveDeposit&);



	ISaveDeposit* operator->()const;


};
