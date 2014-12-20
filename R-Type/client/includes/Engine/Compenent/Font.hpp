#pragma once

#include <string>
#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Font : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Font(std::string font, std::string text);
		~Font();
	
	public:
		void				setFont(std::string);
		const std::string	&getFont() const;

		void				setText(std::string);
		const std::string	&getText() const;

	private:
		std::string				mFont;
		std::string				mText;
};
