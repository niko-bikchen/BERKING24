#pragma once

class DepositFunctor
{
private:
	size_t _daysLasted;
	size_t _daysNeeded;
public:
	DepositFunctor(size_t daysLasted,size_t daysNeeded):_daysLasted(daysLasted),_daysNeeded(daysNeeded){}
	~DepositFunctor() {}
	unsigned long operator()(unsigned long sum) const
	{
		if (_daysLasted == _daysNeeded)
		{
			return sum + sum * _daysNeeded / 366;
		}
		else
		{
			return sum - sum * (_daysLasted - _daysNeeded) / 366;
		}
	}
};
