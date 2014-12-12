#include "Gameplay/GameplaySystem.hpp"
#include "Engine/ComponentType.h"
#include "RTypeClient.hpp"
#include "Engine/ECSManagerNetwork.hpp"
FireSystem::FireSystem()
{
	setComponentNeeded(ComponentType::FIRE);
}

FireSystem::~FireSystem()
{
}

void	FireSystem::process(Entity &entity, uint32_t /* */)
{
	if (entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
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
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::RIGHT);
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
		static_cast<ECSManagerNetwork *>(entity.getEntityManager())->SignalMove(IResource::Direction::LEFT);
	}
}