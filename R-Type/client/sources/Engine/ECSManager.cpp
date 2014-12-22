#include <algorithm>
#include <stdexcept>
#include "Engine/ComponentType.h"
#include "Engine/ECSManager.hpp"
#include "Engine/Entity.hpp"

ECSManager::ECSManager(RTypeClient *client)
: mClient(client), mCurrentId(0)
{

}

ECSManager::~ECSManager()
{
	auto remove = [](Component *component) { delete component; };

	while (!mEntityComponent.empty())
	{
		std::for_each(mEntityComponent.back()->begin(), mEntityComponent.back()->end(), remove);
		mEntityComponent.pop_back();
	}
	for (auto system : mSystem)
	{
		delete system;
	}
}

unsigned int	ECSManager::getCurrentId() const
{
	return	mCurrentId;
}

Entity						&ECSManager::createEntity()
{
	//std::list<Component *> list;

	mEntity.push_back(new Entity(mCurrentId, this));
	mEntityComponent.push_back(new std::list<Component *>); // must initialize an empty list
	mEntityBitset.push_back(0); // bitset set to 0
	mLivingEntity.push_back(true);

	++mCurrentId;
	return *mEntity.back();
}

Entity		&ECSManager::createEntity(const unsigned int id)
{
	if (id >= mCurrentId)
	{
		for (; mCurrentId <= id; ++mCurrentId)
		{
			mEntity.push_back(new Entity(mCurrentId, this));
			mEntityComponent.push_back(new std::list<Component *>);
			mEntityBitset.push_back(0);
			mLivingEntity.push_back(false);
		}
	}
	mLivingEntity.at(id) = true;
	return *mEntity.at(id);
}

bool		ECSManager::isEntityCreated(const unsigned int id) const
{
	try {
		if (mEntity.size() >= id && mLivingEntity.at(id))
			return true;
		return false;
	}
	catch (...) {
		return false;
	}
}

Entity		&ECSManager::getEntity(const int id)
{
	return *mEntity.at(id);
}

bool		ECSManager::addComponent(const unsigned int id, Component *component)
{
	if (component == nullptr)
		return false;

	auto searchId = [&](Component *_component)
	{
		return component->getComponentId() == _component->getComponentId();
	};
	 
	std::list<Component *>	&listComponent = *mEntityComponent.at(id);

	if (std::find_if(listComponent.begin(), listComponent.end(), searchId) == listComponent.end())
	{
		listComponent.push_back(component);
		mEntityBitset.at(id).set(component->getComponentId(), 1);

		return true;
	}

	return false;
}

const std::list<Component *>			&ECSManager::getComponent(const unsigned int id) const {
	return *mEntityComponent.at(id);
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
			try
			{
				if (mLivingEntity.at(i) && currentSystem->haveComponentNeeded(mEntityBitset.at(i)))
				{
					currentSystem->process(*mEntity.at(i), delta);
				}
			}
			catch (...)
			{
			}
		}
	});
}

void	ECSManager::removeEntity(unsigned int id)
{
	auto clean = [](Component *component) {
		delete component;
	};

	std::list<Component *>	&list = *mEntityComponent.at(id);
	std::for_each(list.begin(), list.end(), clean);
	list.clear();
	mEntityBitset.at(id) = 0;
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
		if (mEntityBitset.at(i)[typeToSearch])
			return *mEntity.at(i);
	}
	throw std::runtime_error("Entity not found");
}

void		ECSManager::setFirstId(unsigned int id)
{
	mFirstId = id;
}