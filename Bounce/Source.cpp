#include <SFML/Graphics.hpp>
#include "ColisionResolver.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Bounce");
	srand(time(NULL));
	ColisionResolver manage;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		manage.update();

		window.clear(sf::Color(100,100,100));
		manage.draw(window);
		window.display();
	}

	return 0;
}