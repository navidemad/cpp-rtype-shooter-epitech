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
		std::cout << "FireSystem::process ACTIONS" << std::endl;
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalFire();
	}
}

DownSystem::DownSystem()
{
	setComponentNeeded(ComponentType::DOWN);
}

DownSystem::~DownSystem() { }

void	DownSystem::process(Entity &entity, uint32_t /* */)
{
	if (entity.getEntityManager()->getClient()->getGui()->isPressed("s"))
	{
		std::cout << "DownSystem::process BOTTOM" << std::endl;
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

void	UpSystem::process(Entity &entity, uint32_t /* */)
{
	if (entity.getEntityManager()->getClient()->getGui()->isPressed("z"))
	{
		std::cout << "UpSystem::process IP" << std::endl;
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

void	RightSystem::process(Entity &entity, uint32_t /* */)
{
	if (entity.getEntityManager()->getClient()->getGui()->isPressed("q"))
	{
		std::cout << "RightSystem::process LEFT" << std::endl;
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

void	LeftSystem::process(Entity &entity, uint32_t /* */)
{
	if (entity.getEntityManager()->getClient()->getGui()->isPressed("d"))
	{
		std::cout << "LeftSystem::process RIGHT" << std::endl;
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::RIGHT);
	}
}