#pragma once
#include <iostream>
class IEntity
{
public:
	IEntity() {};
	virtual ~IEntity() {};

	

	friend std::ostream& operator<<(std::ostream& out, const IEntity& b)
	{
		b.do_print(out);
		return out;
	}
private:
	virtual std::ostream& do_print(std::ostream&) const = 0;
	
};
