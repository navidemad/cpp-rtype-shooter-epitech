#pragma once

class ContentManager
{
	// ctor - dtor
	public:
		ContentManager();
		~ContentManager();

	// coplien form
	private:
		ContentManager(ContentManager const &) {}
		ContentManager const	&operator=(ContentManager const &) { return *this; }
};
