#pragma once

class Controllable
{
	// ctor - dtor
	public:
		Controllable();
		~Controllable();

	// coplien form
	private:
		Controllable(Controllable const &) {}
		Controllable const	&operator=(Controllable const &) { return *this; }
};
