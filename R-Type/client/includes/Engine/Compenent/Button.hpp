#pragma once

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
#include <iostream>
class ButtonInput : public Button
{
public:
	ButtonInput(Font *font, void (RTypeClient::*fct)(std::string const &)) : Button(100), mFont(font) { mFct = fct; }
	~ButtonInput() { }

public:
	void	process(Entity &, uint32_t delta);

private:
	Font	*mFont;
	void (RTypeClient::*mFct)(std::string const &);
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
