#pragma once

#include "ComponentType.h"

class Component
{
    // ctor - dtor
    public:
        explicit Component(ComponentType::Type);
        ~Component();

    // copy operators
    public:
        Component(const Component &) = delete;
        Component(Component &&) = delete;
        const Component &operator=(const Component &) = delete;
        const Component &operator=(Component &&) = delete;

	public:
		ComponentType::Type	getComponentId() const;
		void				setComponentId(ComponentType::Type type);


	private:
		ComponentType::Type mCompenentId;
};
