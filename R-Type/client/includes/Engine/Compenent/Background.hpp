#pragma once

#include <list>
#include "../Component.hpp"
#include "../ComponentType.h"
#include "Engine/Compenent/Position.hpp"
#include "NoCopyable.hpp"

class Background : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Background();
		~Background();

	public:
		void				addBackground(Position *);
		std::list<Position *>	&getList();

	private:
		std::list<Position *>		mListBackground;
};
