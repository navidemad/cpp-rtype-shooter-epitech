#include <algorithm>
#include "Engine/ComponentType.h"
#include "Engine/ECSManager.hpp"
#include "Engine/Entity.hpp"

ECSManager::ECSManager(RTypeClient *client)
: mClient(client), mCurrentId(0)
{

}

ECSManager::~ECSManager()
{

}

inline unsigned int	ECSManager::getCurrentId() const
{
	return	mCurrentId;
}

Entity						&ECSManager::createEntity()
{
	std::list<Component *> list;

	mEntity.push_back(Entity(mCurrentId, this));
	mEntityComponent.push_back(list); // must initialize an empty list
	mEntityBitset.push_back(0); // bitset set to 0

	++mCurrentId;
	return mEntity.back();
}

Entity		&ECSManager::getEntity(const int id)
{
	return mEntity.at(id);
}

bool		ECSManager::addComponent(const unsigned int id, Component *component)
{
	auto searchId = [&](Component *_component)
	{
		return component->getComponentId() == _component->getComponentId();
	};
	
	std::list<Component *>	&listComponent = mEntityComponent.at(id);

	if (std::find_if(listComponent.begin(), listComponent.end(), searchId) == listComponent.end())
	{
		listComponent.push_back(component);
		mEntityBitset[id].set(component->getComponentId(), 1);

		return true;
	}

	return false;
}

const std::list<Component *>			&ECSManager::getComponent(const unsigned int id) const {
	return mEntityComponent.at(id);
}

void		ECSManager::addSystem(System *system)
{
	mSystem.push_back(system);
}

void			ECSManager::updateSystem(uint32_t delta)
{
	const size_t	limit = mCurrentId;

	std::for_each(mSystem.begin(), mSystem.end(), [&](System * currentSystem) {
		for (size_t i = 0; i != limit; ++i)
		{
			if (currentSystem->haveComponentNeeded(mEntityBitset[i]))
			{
				currentSystem->process(mEntity[i], delta);
			}
		}
	});
}

void	ECSManager::removeEntity(unsigned int id)
{
	auto clean = [](Component *component) {
		delete component;
	};

	std::list<Component *>	&list = mEntityComponent[id];
	std::for_each(list.begin(), list.end(), clean);
	list.clear();
	mEntityBitset[id] = 0;
}

void	ECSManager::removeAllEntity()
{
	while (!mRemoveId.empty())
	{
		unsigned int	id = mRemoveId.front();
		mRemoveId.pop_front();

		removeEntity(id);
	}
}

Entity		&ECSManager::getEntityWithSpecificCompenent(ComponentType::Type typeToSearch)
{
	const size_t	limit = mCurrentId;

	for (size_t i = 0; i != limit; ++i)
	{
		if (mEntityBitset[i][typeToSearch])
			return mEntity[i];
	}
	throw std::runtime_error("Entity not found");
}