#pragma once
class IEntity
{
public:
	virtual ~IEntity()
	{
	};

	enum Status { MODIFIED, DELETED, UNCHANGED };

	virtual size_t getId() const = 0;
	virtual Status getStatus() const = 0;
	virtual void setStatus(Status) = 0;
};
