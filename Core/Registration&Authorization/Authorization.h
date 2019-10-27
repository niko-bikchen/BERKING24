#pragma once
#include <string>

class Authorization
{
private:
	std::string clientName;
	std::string clientEmail;
	std::string clientPassword;

public:
	Authorization();
	~Authorization();
	void authorize(std::string clientName, std::string clientEmail, std::string clientPassword);
	bool credentialsAreValid(std::string clientName, std::string clientEmail, std::string clientPassword);
	std::string recoverPassword(std::string clientEmail);
};