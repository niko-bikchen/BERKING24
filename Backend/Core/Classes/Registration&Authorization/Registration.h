#pragma once
#include <string>

class Registration
{
private:
	std::string clientName;
	std::string clientEmail;
	std::string clientPassword;
	std::string validationCode;
	std::string generateCode();

public:
	Registration();
	~Registration();

	void registrate(std::string clientName, std::string clientEmail, std::string clientPassword);
	bool clientAlreadyPresent(std::string clientName, std::string clientEmail, std::string clientPassword);
	void sendWebToken(std::string webToken);
	bool isValidWebToken(std::string webToken);
};
