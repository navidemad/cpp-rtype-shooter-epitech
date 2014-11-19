#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>

int		main(void)
{
	sf::RenderWindow window(sf::VideoMode(856, 480), "\\o/");
	sf::CircleShape shape(240.f);
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
		window.draw(shape);
		window.display();
	}
	return (0);
}