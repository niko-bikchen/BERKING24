#pragma once
#include "IClient.h"
#include "CardManager.h"

class CommonClient : public IClient
{
private:
	size_t _id;
	std::string _webToken;
	std::string _name;
	std::string _password;
	std::string _email;
	ModificationType _modificationType = UNCHANGED;

	void setModificationType(ModificationType) override;
public:
	CommonClient(std::string name, std::string email, std::string password)
	{
	}

	~CommonClient()
	{
	}

	size_t getId() const override;

	std::string getWebToken() const override;
	void setWebToken(std::string) override;

	std::string getName() const override;
	
	std::string getPassword() const override;
	void setPassword(std::string) override;

	std::string getEmail() const override;
	void setEmail(std::string) override;

	ModificationType getModificationType() const override;
};
