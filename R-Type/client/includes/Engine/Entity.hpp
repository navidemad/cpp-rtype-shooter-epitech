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

    // copy operators
	public:

	// getter
	public:
		inline unsigned int	getId() const;

	public:
		inline bool										addComponent(Component *);
		inline const std::list<Component *>				&getComponent() const;
		inline std::bitset<ComponentType::LIMIT>		getComponentBit() const;
		
	private:
		const unsigned int	mId;
		ECSManager			*mEntityManager;

};
