//The file was written by Haponenko Vladislav 16.11.2019
#pragma once
#include "IEntity.h"

class IManager 
{
///
///The class IManager is corresponding for a common representation of a classes

public:
	IManager() {};
	virtual ~IManager() {};
	void update()
	{
		return do_update();
	}
private:
	virtual void do_update() = 0;

};
