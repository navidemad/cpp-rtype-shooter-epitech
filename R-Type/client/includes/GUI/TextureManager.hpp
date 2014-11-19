#pragma once

#include "GUI/IResourceManager.hpp"

class TextureManager
{
	// ctor - dtor
	public:
		TextureManager();
		~TextureManager();

	// coplien form
	private:
		TextureManager(TextureManager const &) {}
		TextureManager const	&operator=(TextureManager const &) { return *this; }
};
