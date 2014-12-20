#pragma once

#include "ComponentType.h"
#include "NoCopyable.hpp"

class Component
{
    // ctor - dtor
    public:
        explicit Component(ComponentType::Type);
        virtual ~Component();

	public:
		ComponentType::Type	getComponentId() const;
		void				setComponentId(ComponentType::Type type);


	private:
		ComponentType::Type mCompenentId;
};
