#pragma once

class Collision
{
	// ctor - dtor
	public:
		Collision();
		~Collision();

	// coplien form
	private:
		Collision(Collision const &) {}
		Collision const	&operator=(Collision const &) { return *this; }

};
