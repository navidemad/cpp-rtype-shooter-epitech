#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>

class SpriteModel
{
    // ctor - dtor
    public:
		SpriteModel(std::string const &filename, uint32_t columns, uint32_t lines, sf::IntRect const &rect = sf::IntRect());
		~SpriteModel();

    // copy operators
    public:
        SpriteModel(const SpriteModel &);
        const SpriteModel &operator=(const SpriteModel &);

	// methods
	public:
		sf::Texture const	&getTexture() const;
		sf::IntRect const	&getRect() const;
		sf::Sprite			&getSprite(uint32_t index = 0);
		bool				isLoop() const;
		std::string const	&getFileName() const;
		uint32_t			getCurrentIndex() const;
		uint32_t			getBegin() const;
		uint32_t			getEnd() const;
		uint32_t			getLines() const;
		uint32_t			getColumns() const;
		uint32_t			getX() const;
		uint32_t			getY() const;
		uint32_t			getSize() const;

		void				setAnims(uint32_t begin, uint32_t end);
		void				setCurrentIndex(uint32_t currentIndex);
		void				setLoop(bool enable = true);
	private:
		void				init();

	// attributes
	private:
		sf::Texture					mTexture;
		sf::IntRect					mRect;
		sf::Sprite					mSprite;
		std::vector<sf::Sprite>		mSprites;
		bool						mLoop;
		std::string					mFileName;
		uint32_t					mCurrentIndex;
		uint32_t					mBegin;
		uint32_t					mEnd;
		uint32_t					mColumns;
		uint32_t					mLines;
		uint32_t					mX;
		uint32_t					mY;
};
