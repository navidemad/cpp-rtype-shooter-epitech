#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "Engine/Compenent/Button.hpp"
#include "RTypeClient.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Button.hpp"
#include "Engine/Compenent/TextInput.hpp"

Button::Button(uint32_t cycle) : Component(ComponentType::BUTTON), mCycle(cycle), mTimeElapsed(0)
{

}

Button::~Button()
{

}

bool	Button::hasTimeElapsed() const
{
	return mTimeElapsed > mCycle;
}

void	Button::resetTimer()
{
	mTimeElapsed = 0;
}

void	Button::updateTimer(uint32_t delta)
{
	mTimeElapsed += delta;
}


void	ButtonGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::RTYPE);
	}
	
}

void	ButtonQuitGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		entity.getEntityManager()->getClient()->getGui()->close();
	}
}

void	ButtonMenuGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::MENU);
	}
}

void	ButtonOption::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::OPTION);
	}
	
}

void	ButtonSearchMenu::process(Entity &, uint32_t delta)
{

}

void	ButtonInput::process(Entity &temporyEntity, uint32_t delta)
{
	/*
	ButtonInput	*button = static_cast<ButtonInput *>(temporyEntity.getSpecificComponent(ComponentType::BUTTON));

	Entity &entity = entity.getEntityManager()->getEntity(button->getEntity());

	Font *sprite = static_cast<TextInput *>(entity.getSpecificComponent(ComponentType::TEXTINPUT));
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

//	mTimeElapsed += delta;

	std::string	text = sprite->getText() + entity.getEntityManager()->getClient()->getGui()->getInputText();
	sprite->setText(text);

	if (entity.getEntityManager()->getClient()->getGui()->isPressed("delete") && sprite->getText().size() && mTimeElapsed > 50)
	{
	//	mTimeElapsed = 0;
		text = sprite->getText();
		text = text.substr(0, text.size() - 1);
		sprite->setText(text);
	}
	entity.getEntityManager()->getClient()->getGui()->drawFont(sprite->getFont(), sprite->getText(), pos->getX(), pos->getY(), 100);
	*/
}

unsigned int	ButtonInput::getEntity() const
{
	return mEntity;
}