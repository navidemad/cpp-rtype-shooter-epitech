#pragma once

#include "../Engine/System.hpp"

class DrawableSystem
{
	// ctor - dtor
	public:
		DrawableSystem();
		~DrawableSystem();

	// coplien form
	private:
		DrawableSystem(DrawableSystem const &) {}
		DrawableSystem const	&operator=(DrawableSystem const &) { return *this; }
};
