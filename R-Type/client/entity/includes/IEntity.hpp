#pragma once

#include <list>
#include "Engine/Component.hpp"

class IEntity
{
public:
	virtual ~IEntity() { }

public:
	virtual std::list<Component *>	getComponent() = 0;
};