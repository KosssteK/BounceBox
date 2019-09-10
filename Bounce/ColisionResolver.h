#pragma once
#include "Ball.h"
#include "Wall.h"
#include <vector>

class ColisionResolver
{
	std::vector<Ball> balls;
	std::vector<Wall> walls;
	int a;

public:
	ColisionResolver();
	~ColisionResolver();

	void update();
	void draw(sf::RenderWindow& window);

	void resolveColisions();
};

