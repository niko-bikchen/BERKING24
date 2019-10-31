#pragma once
#include <string>

class Terminal
{
private:
	std::string cardNumber;
	unsigned short cardPIN;
public:
	Terminal();
	~Terminal();

	bool isCardValid(std::string cardNumber, unsigned short cardPIN);
	void replenishAccount(unsigned int sum);
};
