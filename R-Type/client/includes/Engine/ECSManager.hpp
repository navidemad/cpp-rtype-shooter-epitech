#pragma once

class RTypeClient;

#include <vector>
#include <list>
#include <stdint.h>
#include "Entity.hpp"
#include "Component.hpp"
#include "Core/System.hpp"
#include "NoCopyable.hpp"

class ComponentNotFound : public std::exception
{
public:
	const char *what() const throw() { return "Component not found"; }
};

class ECSManager : public NoCopyable
{
    // ctor - dtor
    public:
		ECSManager() : mClient(nullptr), mCurrentId(0) { }
		ECSManager(RTypeClient *);
	virtual ~ECSManager();

	// getter
	public:
		RTypeClient								*getClient() const { return mClient;  }
		void									setClient(RTypeClient *client) { mClient = client; }
		unsigned int							getCurrentId() const;
		void									setFirstId(unsigned int);

	// Entity Manager
	public:
		// Entity
		Entity									&createEntity();
		Entity									&createEntity(const unsigned int);
		Entity									&getEntity(const int);
		Entity									&getEntityWithSpecificCompenent(ComponentType::Type);
		bool									isEntityCreated(const unsigned int) const;
		// Component
		bool									addComponent(const unsigned int, Component *);
		const std::list<Component *>			&getComponent(const unsigned int) const;

		// System
		void									addSystem(System *);
		void									updateSystem(uint32_t);
		virtual void							start() { }
		virtual void							stop() { }

	private:
		void									removeEntity(unsigned int);
		void									removeAllEntity();

	private:
		RTypeClient								*mClient;

	// attribute ECS System
	protected:
		std::vector<Entity>								mEntity;
		std::vector<std::list<Component *> >			mEntityComponent;
		std::vector<std::bitset<ComponentType::LIMIT> >	mEntityBitset;
		std::list<System *>								mSystem;
		std::vector<bool>								mLivingEntity;

		unsigned int									mCurrentId;
		unsigned int									mFirstId;
	protected:
		std::list<unsigned int>							mRemoveId;
};
