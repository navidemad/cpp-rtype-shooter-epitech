#pragma once

class Entity
{
	// ctor - dtor
	public:
		Entity();
		~Entity();

	// coplien form
	private:
		Entity(Entity const &) {}
		Entity const	&operator=(Entity const &) { return *this; }
};
