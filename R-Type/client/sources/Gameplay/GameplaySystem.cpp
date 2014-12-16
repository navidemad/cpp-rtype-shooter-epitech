#include "Gameplay/GameplaySystem.hpp"
#include "Engine/ComponentType.h"
#include "RTypeClient.hpp"
#include "Engine/ECSManagerNetwork.hpp"
#include "Gameplay/Gameplay.hpp"

FireSystem::FireSystem()
{
	setComponentNeeded(ComponentType::FIRE);
}

FireSystem::~FireSystem()
{
}

void	FireSystem::process(Entity &entity, uint32_t delta)
{
	Fire *fire = static_cast<Fire *>(entity.getSpecificComponent(ComponentType::FIRE));

	fire->addDelta(delta);

	if (fire->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		fire->resetTimer();
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalFire();
	}
}

DownSystem::DownSystem()
{
	setComponentNeeded(ComponentType::DOWN);
}

DownSystem::~DownSystem() { }

void	DownSystem::process(Entity &entity, uint32_t delta)
{
	Down *down = static_cast<Down *>(entity.getSpecificComponent(ComponentType::DOWN));

	down->addDelta(delta);
	if (down->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("s"))
	{
		down->resetTimer();
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::BOTTOM);
	}
}

UpSystem::UpSystem()
{
	setComponentNeeded(ComponentType::UP);
}

UpSystem::~UpSystem()
{
}

void	UpSystem::process(Entity &entity, uint32_t delta)
{
	Up *up = static_cast<Up *>(entity.getSpecificComponent(ComponentType::UP));

	up->addDelta(delta);
	if (up->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("z"))
	{
		up->resetTimer();
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::TOP);
	}
}

RightSystem::RightSystem()
{
	setComponentNeeded(ComponentType::RIGHT);
}

RightSystem::~RightSystem()
{
}

void	RightSystem::process(Entity &entity, uint32_t delta)
{
	Right *right = static_cast<Right *>(entity.getSpecificComponent(ComponentType::RIGHT));

	right->addDelta(delta);
	if (right->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("q"))
	{
		right->resetTimer();
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::LEFT);
	}
}

LeftSystem::LeftSystem()
{
	setComponentNeeded(ComponentType::LEFT);
}

LeftSystem::~LeftSystem()
{
}

void	LeftSystem::process(Entity &entity, uint32_t delta)
{
	Left *right = static_cast<Left *>(entity.getSpecificComponent(ComponentType::LEFT));

	right->addDelta(delta);

	if (right->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("d"))
	{
		right->resetTimer();
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::RIGHT);
	}
}