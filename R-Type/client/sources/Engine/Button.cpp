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
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->close();
	}
}

void	ButtonMenuGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::MENU);
	}
}

void	ButtonOption::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::OPTION);
	}
	
}

void	ButtonSearchMenu::process(Entity &/* */, uint32_t/* delta*/)
{

}

void	ButtonInput::process(Entity &entity, uint32_t delta)
{
	std::string	text = mFont->getText() + entity.getEntityManager()->getClient()->getGui()->getInputText();
	mFont->setText(text);

	updateTimer(delta);
	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("delete") && mFont->getText().size())
	{
		text = mFont->getText();
		text = text.substr(0, text.size() - 1);
		mFont->setText(text);
		resetTimer();
	}
}
