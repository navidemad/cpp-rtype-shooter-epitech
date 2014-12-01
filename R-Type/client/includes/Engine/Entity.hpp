#pragma once

class ECSManager;

#include <list>
#include <bitset>
#include "Component.hpp"
#include "ComponentType.h"

class Entity
{
	// ctor - dtor
	public:
		explicit Entity(unsigned int, ECSManager *);
		~Entity();

	// getter
	public:
		unsigned int	getId() const;

	public:
		bool											addComponent(Component *);
		Component										*getSpecificComponent(ComponentType::Type);
		const std::list<Component *>					&getComponent() const;
		std::bitset<ComponentType::LIMIT>				getComponentBit() const;

	public:
		inline ECSManager			*getEntityManager() const { return mEntityManager; }
	private:
		const unsigned int	mId;
		ECSManager			*mEntityManager;

};
