#pragma once

#include <string>
#include "../Component.hpp"
#include "../ComponentType.h"

class Font : public Component
{
	// ctor - dtor
	public:
		Font(std::string font, std::string text);
		~Font();

	// coplien form
	private:
		Font(Font const &) : Component(ComponentType::FONT) {}
		Font const	&operator=(Font const &) { return *this; }
	
	public:
		void				setFont(std::string);
		const std::string	&getFont() const;

		void				setText(std::string);
		const std::string	&getText() const;

	private:
		std::string				mFont;
		std::string				mText;
};
