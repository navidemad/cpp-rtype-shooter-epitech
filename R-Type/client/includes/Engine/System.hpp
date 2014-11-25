#pragma once

#include <bitset>
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"

class System
{
	// ctor - dtor
	public:
		System();
		~System();

	// coplien form
	private:
		System(System const &) {}
		System const	&operator=(System const &) { return *this; }

	public:
		inline bool	haveComponentNeeded(const std::bitset<ComponentType::LIMIT> &component) const {
			const size_t limit = component.size();

			for (size_t i = 0; i != limit; ++i)
			{
				if (component[i])
				{
					if (mComponentNeeded[i] != component[i])
						return false;
				}
			}
			return true;
		}
		inline void			setComponentNeeded(const ComponentType::Type newType);
		virtual void		process(Entity &) = 0;

	private:
		std::bitset	<ComponentType::LIMIT>mComponentNeeded;
};
