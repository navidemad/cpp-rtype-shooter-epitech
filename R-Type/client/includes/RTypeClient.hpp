#pragma once

class RTypeClient
{
	// ctor - dtor
	public:
		RTypeClient();
		~RTypeClient();

	// coplien form
	private:
		RTypeClient(RTypeClient const &) {}
		RTypeClient const	&operator=(RTypeClient const &) { return *this; }
};
