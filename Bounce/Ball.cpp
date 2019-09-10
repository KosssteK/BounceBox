#include "Ball.h"



Ball::Ball(sf::Vector2f position, float radius)
	:velocity(sf::Vector2f(0,0)), shape(radius), radius(radius)
{
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(position);
	mass = 0.2;
	touched = false;
	lastTouchedIndex = 0;
}

Ball::Ball(sf::Vector2f position, float radius, sf::Vector2f side, float mass, int index)
	:velocity(side), shape(radius), radius(radius), mass(mass)
{
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(position);
	touched = false;
	lastTouchedIndex = index;
}

Ball::~Ball()
{
}

void Ball::update()
{
	sf::Vector2f gravity(0,1);

	sf::Vector2f pos = shape.getPosition();
	sf::Vector2f finalVelocityVector = pos + velocity;
	//finalVelocityVector += gravity;
	shape.setPosition(finalVelocityVector);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::Vector2f Ball::getPosition()
{
	return shape.getPosition();
}

float Ball::getRadius()
{
	return radius;
}

float Ball::getMass()
{
	return mass;
}

void Ball::setVelocity(sf::Vector2f vector)
{
	velocity = vector;
}

sf::Vector2f Ball::getVelocity()
{
	return velocity;
}

bool Ball::isTouched()
{
	return touched;
}

void Ball::setTouched(bool isTouched)
{
	touched = isTouched;
}

int Ball::getLastTouchedIndex()
{
	return lastTouchedIndex;
}

void Ball::setLastTouchedIndex(int index)
{
	lastTouchedIndex = index;
}
