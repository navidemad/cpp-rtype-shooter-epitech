#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class TextureManager : public IResourceManager<std::map<std::string, sf::Sprite>>
{
    // ctor - dtor
    private:
        explicit TextureManager();
    public:
        virtual ~TextureManager();

    // copy operators
    public:
        TextureManager(const TextureManager &) = delete;
        TextureManager(TextureManager &&) = delete;
        const TextureManager &operator=(const TextureManager &) = delete;
        const TextureManager &operator=(TextureManager &&) = delete;

	// instance
	public:
		static std::shared_ptr<TextureManager>	getInstance(void);
	private:
		static std::shared_ptr<TextureManager>	mInstance;

	// methods
	public:
		virtual void									loadResources();
		virtual void									unloadResources();
		virtual std::map<std::string, sf::Sprite> const	&getResources() const;

	// attributes
	private:
		std::map<std::string, sf::Sprite>	mListResources;
};
