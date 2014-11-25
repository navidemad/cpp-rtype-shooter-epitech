#include <iostream>
#include "GUI/SFMLGraphic.hpp"

int		main(void)
{
/*	sf::RenderWindow window(sf::VideoMode(856, 480), "\\o/");
	sf::CircleShape shape(240.f);
	sf::Texture	texture;
	sf::Sprite sprite;

	if (!texture.loadFromFile("assets/sprites/r-typesheet7.gif"))
		throw std::exception("NOOOOOO ...");
	sprite.setTexture(texture);
	shape.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}*/
	SFMLGraphic	sg;

	sg.clear();
	sg.drawSprite(0, 0, 0);
	sg.show();
    #if defined(__OS_WINDOWS__)
        system("PAUSE");
    #endif
	return (0);
}
