#include <string>
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "Engine/Compenent/TextInput.hpp"
#include "Engine/Compenent/Font.hpp"
#include "RTypeClient.hpp"
#include <iostream>

TextInput::TextInput(std::string const &font, std::string const &text) : Font(font, text)
{
	setComponentId(ComponentType::TEXTINPUT);
}

TextInput::~TextInput()
{

}