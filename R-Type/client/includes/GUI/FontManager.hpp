#pragma once

class FontManager
{
	// ctor - dtor
	public:
		FontManager();
		~FontManager();

	// coplien form
	private:
		FontManager(FontManager const &) {}
		FontManager const	&operator=(FontManager const &) { return *this; }
};
