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
		Entity(unsigned int, ECSManager *);
		~Entity();

	// coplien form
	private:
//		Entity(Entity const &/* */) : mId(0) {}
//		Entity const	&operator=(Entity const &) { return *this; }

	// getter
	public:
		inline const unsigned int	getId() const;

	public:
		inline bool										addComponent(Component *);
		inline const std::list<Component *>				&getComponent() const;
		inline std::bitset<ComponentType::LIMIT>		getComponentBit() const;
		
	private:
		const unsigned int	mId;
		ECSManager			*mEntityManager;

};
