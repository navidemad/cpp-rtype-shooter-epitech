#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"

class ScriptSystem : public System
{
    // ctor - dtor
    public:
		explicit ScriptSystem();
		~ScriptSystem();

	public:
		void	process(Entity &, uint32_t);

    // copy operators
    public:
		ScriptSystem(const ScriptSystem &) = delete;
		ScriptSystem(ScriptSystem &&) = delete;
		const ScriptSystem &operator=(const ScriptSystem &) = delete;
		const ScriptSystem &operator=(ScriptSystem &&) = delete;
};
