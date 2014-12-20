#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Engine/Compenent/List.hpp"
#include "Engine/Compenent/Font.hpp"
#include "NoCopyable.hpp"

class ListSystem : public System
{
    // ctor - dtor
    public:
		ListSystem();
		~ListSystem() { }

		void	process(Entity &, uint32_t);

	private:
		void	displayRoom(Entity &, Font *, Position *, List *);
};
