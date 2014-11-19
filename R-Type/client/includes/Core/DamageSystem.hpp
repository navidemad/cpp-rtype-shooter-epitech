#pragma once

class DamageSystem
{
	// ctor - dtor
	public:
		DamageSystem();
		~DamageSystem();

	// coplien form
	private:
		DamageSystem(DamageSystem const &) {}
		DamageSystem const	&operator=(DamageSystem const &) { return *this; }
};
