#pragma once

#include <list>
#include "../Component.hpp"
#include "../ComponentType.h"
#include "Engine/Compenent/Position.hpp"

class Background : public Component
{
	// ctor - dtor
	public:
		Background();
		~Background();

	// coplien form
	private:
		Background(Background const &) : Component(ComponentType::MOVABLE) {}
		Background const	&operator=(Background const &) { return *this; }

	public:
		void				addBackground(Position *);
		std::list<Position *>	&getList();

	private:
		std::list<Position *>		mListBackground;
};
