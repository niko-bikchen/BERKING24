#pragma once
class IManager
{
public:
	virtual ~IManager()
	{
	};
	
	virtual void update() = 0;
};
