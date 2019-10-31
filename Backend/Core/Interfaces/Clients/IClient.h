#pragma once
#include <string>
#include  "IEntity.h"

class IClient : public IEntity
{
public:
	virtual ~IClient()
	{
	};

	virtual std::string getWebToken() const = 0;
	virtual void setWebToken(std::string) = 0;

	virtual std::string getName() const = 0;
	virtual std::string getPassword() const = 0;
	virtual void setPassword(std::string) = 0;

	virtual std::string getEmail() const = 0;
	virtual void setEmail(std::string) = 0;
};
