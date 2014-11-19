#pragma once

class CollisionSystem
{
	// ctor - dtor
	public:
		CollisionSystem();
		~CollisionSystem();

	// coplien form
	private:
		CollisionSystem(CollisionSystem const &) {}
		CollisionSystem const	&operator=(CollisionSystem const &) { return *this; }

};
