#include <algorithm>
#include "Engine/ECSManagerNetwork.hpp"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "Engine/Compenent/Button.hpp"
#include "RTypeClient.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Button.hpp"
#include "Engine/Compenent/TextInput.hpp"

Button::Button(uint32_t cycle) : Component(ComponentType::BUTTON), mTimeElapsed(0), mCycle(cycle)
{

}

Button::~Button()
{

}

bool	Button::hasTimeElapsed() const
{
	return mTimeElapsed / 1000 > mCycle;
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
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::CREATE_MENU);
	}
}

void	ButtonQuitGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->getGui()->close();
	}
}

void	ButtonMenuGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::MENU);
	}
}

void	ButtonOption::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::OPTION);
	}
	
}

void	ButtonSearchMenu::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::SEARCH_MENU);
	}
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
	RTypeClient *client = entity.getEntityManager()->getClient();
	(client->*mFct)(text);
}

void	ButtonStateInput::process(Entity &entity, uint32_t delta)
{
	bool enable = (mFont->getText() == "yes");

	updateTimer(delta);
	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		enable = !enable;
		mFont->setText(enable ? "yes" : "no");
		resetTimer();
	}
	RTypeClient *client = entity.getEntityManager()->getClient();
	(client->*mFct)(enable);
}

void	ButtonKeyInput::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);
	if (hasTimeElapsed())
	{
		resetTimer();

		// search current value
		std::vector<std::string>::const_iterator it;
		for (it = mList.begin(); it != mList.end() && *it != mFont->getText(); ++it) {}
		if (it == mList.end())
			it = mList.begin();

		RTypeClient *client = entity.getEntityManager()->getClient();
		if (entity.getEntityManager()->getClient()->getGui()->isPressed("left"))
		{
			if (it != mList.begin())
				--it;
			mFont->setText(*it);
			(client->*mHandler)(mFont->getText());
		}
		else if (entity.getEntityManager()->getClient()->getGui()->isPressed("right"))
		{
			if (it != mList.end() - 1)
				++it;
			mFont->setText(*it);
			(client->*mHandler)(mFont->getText());
		}
	}
}

void	ButtonCreateGame::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		if (entity.getEntityManager()->getClient()->createGame() == true)
		{
			entity.getEntityManager()->getClient()->getGui()->playSound("option");
			entity.getEntityManager()->stop();
			entity.getEntityManager()->getClient()->setIdGame(RTypeClient::RTYPE);
		}
	}
}

void	ButtonBackGameAndSave::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::MENU);
	}
}

void	ButtonArtwork::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::ARTWORK);
	}
}

void	ButtonConnect::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->getClient()->connectToServer();
	}
}

void	ButtonNetworkOption::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::NETWORK);
	}
}

void	ButtonGameOption::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::GAME);
	}
}

void	ButtonAudioOption::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
		entity.getEntityManager()->getClient()->getGui()->playSound("option");
		entity.getEntityManager()->stop();
		entity.getEntityManager()->getClient()->setIdGame(RTypeClient::AUDIO);
	}
}
