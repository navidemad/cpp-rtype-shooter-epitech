#include <string>
#include <iostream>
#include "Core/TextInputSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "RTypeClient.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Button.hpp"
#include "Engine/Compenent/TextInput.hpp"

TextInputSystem::TextInputSystem()
{
	setComponentNeeded(ComponentType::TEXTINPUT);
	setComponentNeeded(ComponentType::MOVABLE);
	mTimeElapsed = 0;
}

TextInputSystem::~TextInputSystem()
{

}

void		TextInputSystem::process(Entity &/* entity */, uint32_t /* delta */)
{
/*	Font *sprite = static_cast<TextInput *>(entity.getSpecificComponent(ComponentType::TEXTINPUT));
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

	mTimeElapsed += delta;

	std::string	text = sprite->getText() + entity.getEntityManager()->getClient()->getGui()->getInputText();
	sprite->setText(text);
	
	if (entity.getEntityManager()->getClient()->getGui()->isPressed("delete") && sprite->getText().size() && mTimeElapsed > 50)
	{
		mTimeElapsed = 0;
		text = sprite->getText();
		text = text.substr(0, text.size() - 1);
		sprite->setText(text);
	}
	entity.getEntityManager()->getClient()->getGui()->drawFont(sprite->getFont(), sprite->getText(), pos->getX(), pos->getY(), 100);*/
}