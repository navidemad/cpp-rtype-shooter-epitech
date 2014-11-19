#pragma once

class Component
{
	// ctor - dtor
	public:
		Component();
		~Component();

	// coplien form
	private:
		Component(Component const &) {}
		Component const	&operator=(Component const &) { return *this; }
};
