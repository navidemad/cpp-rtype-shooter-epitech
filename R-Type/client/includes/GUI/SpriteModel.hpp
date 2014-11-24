#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>

class SpriteModel
{
	// ctor - dtor
	public:
		SpriteModel(std::string const &filename);
		~SpriteModel();

	// coplien form
	public:
		SpriteModel(SpriteModel const &) {}
		SpriteModel const	&operator=(SpriteModel const &) { return *this; }

	// methods
	public:
		uint32_t			getCurrentIndex() const;
		bool				isLoop() const;
		std::string const	&getFileName() const;
		sf::Sprite const	&getSprite() const;

		void				setAnims(uint32_t begin, uint32_t end);
		void				setAnims(std::vector<sf::Sprite>::iterator begin, std::vector<sf::Sprite>::iterator end);
		void				setCurrentIndex(uint32_t currentIndex);
		void				setLoop(bool enable = true);
	private:
		void				init();

	// attributes
	private:
		std::vector<sf::Sprite>	mSprites;
		bool					mLoop;
		std::string				mFileName;
		uint32_t				mCurrentIndex;
		uint32_t				mBegin;
		uint32_t				mEnd;
		sf::Texture				mTexture;
		sf::Sprite				mSprite;
};
