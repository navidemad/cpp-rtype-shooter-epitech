#pragma once

class MovementSystem
{
	// ctor - dtor
	public:
		MovementSystem();
		~MovementSystem();

	// coplien form
	private:
		MovementSystem(MovementSystem const &) {}
		MovementSystem const	&operator=(MovementSystem const &) { return *this; }
};
