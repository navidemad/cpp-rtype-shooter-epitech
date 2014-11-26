#include "Engine/Compenent/Font.hpp"
#include "Engine/ComponentType.h"

Font::Font(std::string font, std::string text)
: Component(ComponentType::FONT), mFont(font), mText(text)
{

}

Font::~Font()
{
	
}

void				Font::setFont(std::string font)
{
	mFont = font;
}
const std::string	&Font::getFont() const
{
	return mFont;
}

void				Font::setText(std::string text)
{
	mText = text;
}

const std::string	&Font::getText() const
{
	return mText;
}
