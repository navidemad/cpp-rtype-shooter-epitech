#pragma once

class Position
{
	// ctor - dtor
	public:
		Position();
		~Position();

	// coplien form
	private:
		Position(Position const &) {}
		Position const	&operator=(Position const &) { return *this; }
};
