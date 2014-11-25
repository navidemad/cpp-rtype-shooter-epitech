#pragma once

class RTypeClient;

#include <vector>
#include <list>
#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"

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
	private:
		inline RTypeClient			&getClient() const;
		inline const unsigned int	getCurrentId() const;

	// Entity Manager
	public:
		// Entity
		Entity						&createEntity();
		inline Entity				&getEntity(const int);

		// Component
		inline bool								addComponent(const unsigned int, Component *);
		inline const std::list<Component *>		&getComponent(const unsigned int) const;

		// System
		void						addSystem(System *);
		void						updateSystem();

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
