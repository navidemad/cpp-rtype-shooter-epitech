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
		const ComponentType::Type	getComponentId() const;

	private:
		const ComponentType::Type mCompenentId;
};
