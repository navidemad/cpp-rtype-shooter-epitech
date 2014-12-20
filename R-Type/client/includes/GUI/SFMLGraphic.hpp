#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IGraphic.hpp"
#include "GUI/ContentManager.hpp"
#include "Core/InputManager.hpp"
#include "NoCopyable.hpp"

class SFMLGraphic : public NoCopyable, public IGraphic
{
    // ctor - dtor
    private:
        SFMLGraphic();
	public:
        virtual ~SFMLGraphic();

	// instance
	public:
		static std::shared_ptr<IGraphic>	getInstance();
	private:
		static std::shared_ptr<IGraphic>	mInstance;

	// public methods
	public:
		bool				drawSprite(std::string const &key, uint64_t delta, float x, float y, uint32_t id);
		bool				drawFont(std::string const &key, std::string const &strn, float x, float y, uint32_t size);
		bool				playMusic(std::string const &key, bool onLoop = true);
		bool				playSound(std::string const &key, bool onLoop = false);
		void				stopMusic();
		void				stopSound(std::string const &key);
		void				setVolume(std::string const &key, float volume = 100.0);
		std::string	const	&getInputText() const;

		bool				isOpen() const;
		void				handleEvent();
		void				init();
		void				update();
		void				clear();
		void				show();
		bool				isPressed(std::string const &);
		uint64_t			getDelta();
		void				close();

		sf::RenderWindow	&getWindow();
		void				setScale(std::string const &key, float sizeX, float sizeY);

	// attributes
	private:
		sf::RenderWindow					mWindow;
		std::map<sf::Event, std::string>	mKeyEvents;
		ContentManager						mContentManager;
		InputManager						mInputManager;
		sf::Clock							mDeltaClock;
		sf::Music							mMusic;
		std::string							mMusicCurrentKey;
		std::map<uint32_t, uint64_t>		mIdTimeElapse;

#define TIME 1000000
};
