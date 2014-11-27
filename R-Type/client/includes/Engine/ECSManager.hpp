#pragma once

class RTypeClient;

#include <vector>
#include <list>
#include "Entity.hpp"
#include "Component.hpp"
#include "../Core/System.hpp"

class ECSManager
{
    // ctor - dtor
    public:
        explicit ECSManager(RTypeClient *);
        ~ECSManager();

    // copy operators
    public:
        ECSManager(const ECSManager &) = delete;
        ECSManager(ECSManager &&) = delete;
        const ECSManager &operator=(const ECSManager &) = delete;
        const ECSManager &operator=(ECSManager &&) = delete;

	// getter
	public:
		RTypeClient			*getClient() const { return mClient;  }
		unsigned int		getCurrentId() const;

	// Entity Manager
	public:
		// Entity
		Entity						&createEntity();
		Entity						&getEntity(const int);

		// Component
		bool									addComponent(const unsigned int, Component *);
		const std::list<Component *>			&getComponent(const unsigned int) const;

		// System
		void						addSystem(System *);
		void						updateSystem(float);

	private:
		RTypeClient									*mClient;

	// attribute ECS System
	private:
		std::vector<Entity>								mEntity;
		std::vector<std::list<Component *> >			mEntityComponent;
		std::vector<std::bitset<ComponentType::LIMIT> >	mEntityBitset;
		std::list<System *>								mSystem;
		unsigned int									mCurrentId;

};
