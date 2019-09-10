#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
	sf::Vector2f velocity;
	sf::CircleShape shape;
	float radius;
	float mass;
	bool touched;
	int lastTouchedIndex;

public:
	Ball(sf::Vector2f position, float radius);
	Ball(sf::Vector2f position, float radius, sf::Vector2f side, float mass, int index);
	~Ball();

	void update();
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition();
	float getRadius();
	float getMass();
	void setVelocity(sf::Vector2f vector);
	sf::Vector2f getVelocity();
	bool isTouched();
	void setTouched(bool isTouched);
	int getLastTouchedIndex();
	void setLastTouchedIndex(int index);
};

