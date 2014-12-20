#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"
#include "NoCopyable.hpp"

class ScriptSystem : public System
{
    // ctor - dtor
    public:
		ScriptSystem();
		~ScriptSystem();

	public:
		void	process(Entity &, uint32_t);

};
