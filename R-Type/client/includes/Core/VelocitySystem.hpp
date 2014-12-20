#pragma once

#include <cstdint>
#include "Engine/Entity.hpp"
#include "Core/System.hpp"
#include "NoCopyable.hpp"
#include "NoCopyable.hpp"

class VelocitySystem : public System
{
    // ctor - dtor
    public:
		VelocitySystem();
		~VelocitySystem();

	public:
		void	process(Entity &, uint32_t);

};
