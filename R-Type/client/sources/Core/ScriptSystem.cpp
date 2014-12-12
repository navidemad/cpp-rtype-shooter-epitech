#include "Core/ScriptSystem.hpp"
#include "Engine/ComponentType.h"

ScriptSystem::ScriptSystem()
{
	setComponentNeeded(ComponentType::SCRIPT);
}

ScriptSystem::~ScriptSystem()
{

}

void	ScriptSystem::process(Entity &/* */, uint32_t /* */)
{

}
