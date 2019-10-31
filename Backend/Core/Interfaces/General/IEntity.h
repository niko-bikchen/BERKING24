#pragma once
class IEntity
{
public:
	virtual ~IEntity()
	{
	};

	enum ModificationType { MODIFIED, DELETED, UNCHANGED };

	virtual size_t getId() const = 0;
	virtual ModificationType getModificationType() const = 0;
	virtual void setModificationType(ModificationType) = 0;
};
