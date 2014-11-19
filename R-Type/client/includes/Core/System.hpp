#pragma once

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
};
