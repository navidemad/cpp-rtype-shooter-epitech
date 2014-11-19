#pragma once

class SFMLGraphic
{
	// ctor - dtor
	public:
		SFMLGraphic();
		~SFMLGraphic();

	// coplien form
	private:
		SFMLGraphic(SFMLGraphic const &) {}
		SFMLGraphic const	&operator=(SFMLGraphic const &) { return *this; }
};
