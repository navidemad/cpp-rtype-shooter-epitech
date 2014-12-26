#pragma once

#include <string>
#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Font : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Font(const std::string &font, const std::string &text);
		~Font();

	public:
		void				setFont(const std::string &);
		const std::string	&getFont() const;

		void				setText(const std::string &);
		const std::string	&getText() const;

	private:
		std::string				mFont;
		std::string				mText;
};
