#include "Wall.h"

Wall::Wall(sf::Vector2f position, float width, float height)
	:shape(sf::RectangleShape(sf::Vector2f(width, height))), dimentions(width, height)
{
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Black);
}

Wall::~Wall()
{
}

sf::Vector2f Wall::getPosition()
{
	return shape.getPosition();
}

sf::Vector2f Wall::getDimentions()
{
	return dimentions;
}

void Wall::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}