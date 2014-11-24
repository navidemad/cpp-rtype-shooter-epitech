#pragma once

#include "ComponentType.h"

class Component
{
	// ctor - dtor
	public:
		Component(ComponentType::Type);
		~Component();

	// coplien form
	private:
//		Component(Component const &) : mCompenentId(ComponentType::INVALID) {}
//		Component const	&operator=(Component const &) { return *this; }

	public:
		const ComponentType::Type	getComponentId() const;

	private:
		const ComponentType::Type mCompenentId;
};
