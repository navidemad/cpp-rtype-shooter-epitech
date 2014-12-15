#pragma once

#include <string>
#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Compenent/Font.hpp"

class TextInput : public Font
{
	// ctor - dtor
	public:
		TextInput(std::string const &, std::string const &);
		~TextInput();

	// coplien form
	private:
	//		TextInput(TextInput const &) : Font(ComponentType::TEXTINPUT) {}
	//	TextInput const	&operator=(TextInput const &) { return *this; }

	public:
		void			process(Entity &);
};