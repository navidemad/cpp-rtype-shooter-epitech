#pragma once

#include <sstream>

#include "RTypeClient.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Compenent/Font.hpp"
#include "NoCopyable.hpp"

class Button : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Button(uint32_t);
		virtual ~Button();

	protected:
		bool	hasTimeElapsed() const;
		void	resetTimer();
		void	updateTimer(uint32_t delta);

	public:
		virtual void	process(Entity &, uint32_t delta) = 0;

	private:
		uint32_t	mTimeElapsed;
		uint32_t	mCycle;
};

class ButtonGame : public Button
{
	public:
		ButtonGame() : Button(100) { }
		~ButtonGame() { }

	public:
		void	process(Entity &, uint32_t delta);
};

class ButtonBackGameAndSave : public Button
{
public:
	ButtonBackGameAndSave() : Button(100) { }
	~ButtonBackGameAndSave() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonQuitGame : public Button
{
public:
	ButtonQuitGame() : Button(100) { }
	~ButtonQuitGame() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonMenuGame : public Button
{
public:
	ButtonMenuGame() : Button(100) { }
	~ButtonMenuGame() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonOption : public Button
{
public:
	ButtonOption() : Button(100) { }
	~ButtonOption() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonInput : public Button
{
public:
	ButtonInput(Font *font, void (RTypeClient::*fct)(std::string const &)) : Button(100), mFont(font), mFct(fct) {}
	~ButtonInput() { }

public:
	void	process(Entity &, uint32_t delta);

private:
	Font	*mFont;
	void	(RTypeClient::*mFct)(std::string const &);
};

class ButtonStateInput : public Button
{
public:
	ButtonStateInput(Font *font, void (RTypeClient::*fct)(bool)) : Button(1024), mFont(font), mFct(fct) {}
	~ButtonStateInput() { }

public:
	void	process(Entity &, uint32_t delta);

private:
	Font	*mFont;
	void	(RTypeClient::*mFct)(bool);
};

template<typename T>
class ButtonKeyInput : public Button
{
	public:
		ButtonKeyInput(Font *font, void(RTypeClient::*handler)(std::string const &), std::vector<T> const &list) : 
			Button(100), mFont(font), mHandler(handler), mList(list) {}
		~ButtonKeyInput() {}

	public:
		void	process(Entity &entity, uint32_t delta)
		{
			updateTimer(delta);
			if (hasTimeElapsed())
			{
				resetTimer();

				// get value from Font
				std::istringstream buffer(mFont->getText());
				T value;
				buffer >> value;

				// search value
				std::vector<T>::const_iterator it;
				for (it = mList.begin(); it != mList.end() && *it != value; ++it) { }
				if (it == mList.end())
					it = mList.begin();

				RTypeClient *client = entity.getEntityManager()->getClient();
				if (entity.getEntityManager()->getClient()->getGui()->isPressed("left"))
				{
					if (it != mList.begin())
						--it;
					mFont->setText(std::to_string(*it));
					(client->*mHandler)(mFont->getText());
				}
				else if (entity.getEntityManager()->getClient()->getGui()->isPressed("right"))
				{
					if (it != mList.end() - 1)
						++it;
					mFont->setText(std::to_string(*it));
					(client->*mHandler)(mFont->getText());
				}
			}
		}

	private:
		Font					*mFont;
		void					(RTypeClient::*mHandler)(std::string const &);
		std::vector<T> const	mList;
};

class ButtonVolumeMusic : public Button
{
	public:
		ButtonVolumeMusic(Font *font, void (RTypeClient::*fct)(std::string const &)) : Button(100), mFont(font), mFct(fct) {}
		~ButtonVolumeMusic() {}

	public:
		void	process(Entity &, uint32_t delta);

	private:
		Font	*mFont;
		void	(RTypeClient::*mFct)(std::string const &);
};

class ButtonSearchMenu : public Button
{
	public:
		ButtonSearchMenu() : Button(100) {}
		~ButtonSearchMenu() {}

	public:
		void	process(Entity &, uint32_t delta);
};

class ButtonCreateGame : public Button
{
public:
	ButtonCreateGame() : Button(100) {}
	~ButtonCreateGame() {}

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonArtwork : public Button
{
public:
	ButtonArtwork() : Button(100) {}
	~ButtonArtwork() {}

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonConnect : public Button
{
public:
	ButtonConnect() : Button(100) {}
	~ButtonConnect() {}

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonNetworkOption : public Button
{
public:
	ButtonNetworkOption() : Button(100) {}
	~ButtonNetworkOption() {}

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonGameOption : public Button
{
public:
	ButtonGameOption() : Button(100) {}
	~ButtonGameOption() {}

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonAudioOption : public Button
{
public:
	ButtonAudioOption() : Button(100) {}
	~ButtonAudioOption() {}

public:
	void	process(Entity &, uint32_t delta);
};
