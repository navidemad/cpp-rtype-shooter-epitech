#pragma once

class Script
{
	// ctor - dtor
	public:
		Script();
		~Script();

	// coplien form
	private:
		Script(Script const &) {}
		Script const	&operator=(Script const &) { return *this; }
};
