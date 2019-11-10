#pragma once
#include "IEntity.h"

class IManager
{
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
