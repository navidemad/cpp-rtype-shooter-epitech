#pragma once

class Drawable
{
	// ctor - dtor
	public:
		Drawable();
		~Drawable();

	// coplien form
	private:
		Drawable(Drawable const &) {}
		Drawable const	&operator=(Drawable const &) { return *this; }
};
