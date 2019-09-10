#pragma once
#include <SFML/Graphics.hpp>


class Wall
{
	sf::RectangleShape shape;
	sf::Vector2f dimentions;

public:
	Wall(sf::Vector2f position, float width, float height);
	~Wall();

	sf::Vector2f getPosition();
	sf::Vector2f getDimentions();
	void draw(sf::RenderWindow& window);
};

