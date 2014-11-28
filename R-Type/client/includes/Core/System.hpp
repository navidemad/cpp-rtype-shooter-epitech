#pragma once

#include <bitset>
#include <stdint.h>
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
				if (mComponentNeeded[i])
				{
					if (mComponentNeeded[i] != component[i])
					{
						return false;
					}
				}
			}

			return true;
		}
		void				setComponentNeeded(const ComponentType::Type newType);
		virtual void		process(Entity &, uint32_t) = 0;

	private:
		std::bitset	<ComponentType::LIMIT>mComponentNeeded;
};
