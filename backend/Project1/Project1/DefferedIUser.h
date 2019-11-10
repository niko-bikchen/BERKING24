#pragma once
#include "IUser.h"
class DefferedIUser
{
private:
	struct UserRep;
	UserRep* _userRep;

	IUser& operator*()const;
public:
	DefferedIUser(std::string wT, std::string name, std::string password, std::string email,
		const std::list<std::string>& cards = {});
	DefferedIUser(const DefferedIUser&);
	~DefferedIUser();
	DefferedIUser& operator=(const DefferedIUser&);



	IUser* operator->()const;


};