#pragma once

#include <string>
#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Compenent/Font.hpp"
#include "NoCopyable.hpp"

class TextInput : public Font
{
	// ctor - dtor
	public:
		TextInput(std::string const &, std::string const &);
		~TextInput();

	public:
		void			process(Entity &);
};