#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IGraphic.hpp"
#include "GUI/ContentManager.hpp"
#include "Core/InputManager.hpp"

class SFMLGraphic : public IGraphic
{
    // ctor - dtor
    private:
        SFMLGraphic();
	public:
        virtual ~SFMLGraphic();

    // copy operators
    public:
        SFMLGraphic(const SFMLGraphic &) = delete;
        SFMLGraphic(SFMLGraphic &&) = delete;
        const SFMLGraphic &operator=(const SFMLGraphic &) = delete;
        const SFMLGraphic &operator=(SFMLGraphic &&) = delete;

	// instance
	public:
		static std::shared_ptr<IGraphic>	getInstance();
	private:
		static std::shared_ptr<IGraphic>	mInstance;

	// public methods
	public:
		bool				drawSprite(std::string const &key, uint64_t delta, float x, float y, uint32_t id);
		bool				drawFont(std::string const &key, std::string const &str, float x, float y, uint32_t size);
		bool				playMusic(std::string const &key, bool onLoop = true);
		bool				playSound(std::string const &key, bool onLoop = false);
		void				stopMusic();
		void				stopSound(std::string const &key);
		void				setVolume(std::string const &key, float volume = 100.0);
		std::string	const	&getInputText() const;

//		void				loadSprite(std::string const &key, std::string const &path);
//		void				loadSound(std::string const &key, std::string const &path);

		bool				isOpen() const;
		void				handleEvent();
		void				init();
		void				update();
		void				clear();
		void				show();
		bool				isPressed(std::string);
		uint64_t			getDelta();
		void				close();

		sf::RenderWindow	&getWindow();
		void				setScale(std::string const &key, float sizeX, float sizeY);

	// attributes
	private:
		sf::RenderWindow					mWindow;
		std::map<sf::Event, std::string>	mKeyEvents;
public:
		ContentManager						mContentManager;
private:
		InputManager						mInputManager;
		sf::Clock							mDeltaClock;
		sf::Music							mMusic;
		std::string							mMusicCurrentKey;
		std::map<uint32_t, uint64_t>		mIdTimeElapse;
};
