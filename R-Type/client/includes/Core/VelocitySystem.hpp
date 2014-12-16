#pragma once

#include <cstdint>
#include "Engine/Entity.hpp"
#include "Core/System.hpp"

class VelocitySystem : public System
{
    // ctor - dtor
    public:
		explicit VelocitySystem();
		~VelocitySystem();

	public:
		void	process(Entity &, uint32_t);

    // copy operators
    public:
		VelocitySystem(const VelocitySystem &) = delete;
		VelocitySystem(VelocitySystem &&) = delete;
		const VelocitySystem &operator=(const VelocitySystem &) = delete;
		const VelocitySystem &operator=(VelocitySystem &&) = delete;
};
