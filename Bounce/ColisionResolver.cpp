#include "ColisionResolver.h"
#include <math.h>
#include <iostream>
#include <algorithm>

float dotProduct(sf::Vector2f v1, sf::Vector2f v2) {
	return (v1.x*v2.x) + (v1.y*v2.y);
}

ColisionResolver::ColisionResolver()
{
	float vel = 7;
	float rad = 12;
	a = 0;

	for (int i = 0; i < 50; i++) {
		sf::Vector2f randPos(rand() % 700+50, rand() % 300+50);
		sf::Vector2f randVec(rand() % 5, rand() % 5);
		float randMass = rand() % 100;
	
		balls.push_back(Ball(randPos, rad, randVec, randMass, balls.size()));
	}

	//for (int i = 0; i < 50; i++) {
	//	sf::Vector2f randPos(rand() % 700 + 50, rand() % 300 + 50);
	//	sf::Vector2f randVec(rand() % 2 - 0.5, rand() % 2 + 1);
	//	float randMass = rand() % 100;
	//
	//	balls.push_back(Ball(randPos, rad, randVec, randMass, balls.size()));
	//}
	//balls.push_back(Ball(sf::Vector2f(200, 200), rad, sf::Vector2f(vel, 0), 50, balls.size()));
	//balls.push_back(Ball(sf::Vector2f(600, 180), rad, sf::Vector2f(-vel, 0), 10, balls.size()));
	//balls.push_back(Ball(sf::Vector2f(400, 300), rad, sf::Vector2f(vel, vel), 4, balls.size()));
	//balls.push_back(Ball(sf::Vector2f(100, 300), rad, sf::Vector2f(vel, 0), 4, balls.size()));

	//balls.push_back(Ball(sf::Vector2f(100, 300), 40, sf::Vector2f(vel, 0), 4, balls.size()));
	//balls.push_back(Ball(sf::Vector2f(400, 300), 40, sf::Vector2f(-vel, 0), 4, balls.size()));


	walls.push_back(Wall(sf::Vector2f(0, 550), 800, 50));
	walls.push_back(Wall(sf::Vector2f(0, 0), 800, 50));
	walls.push_back(Wall(sf::Vector2f(750, 0), 50, 600));
	walls.push_back(Wall(sf::Vector2f(0, 0), 50, 600));


	walls.push_back(Wall(sf::Vector2f(200, 200), 50, 50));
}


ColisionResolver::~ColisionResolver()
{
}

void ColisionResolver::update()
{
	
	resolveColisions();

	for (int i = 0; i < balls.size(); i++) {
		balls[i].update();
	}
	
}

void ColisionResolver::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < balls.size(); i++) {
		balls[i].draw(window);
	}
	for (int i = 0; i < walls.size(); i++) {
		walls[i].draw(window);
	}
}

void ColisionResolver::resolveColisions()
{
	for (int i = 0; i < balls.size(); i++) {
		for (int j = 0; j < balls.size(); j++) {
			//std::cout << "------>>  " << balls[i].isTouched() << std::endl;
			//std::cout << "[adadada] " <<  balls[i].getLastTouchedIndex() << std::endl;
			if (i != j && balls[i].getLastTouchedIndex() != j) {
				sf::Vector2f mainBallPosition = balls[i].getPosition();
				sf::Vector2f currentBallPosition = balls[j].getPosition();
				float distance = sqrt(pow(mainBallPosition.x - currentBallPosition.x, 2) + pow(mainBallPosition.y - currentBallPosition.y, 2));
				if (distance < (balls[i].getRadius() + balls[j].getRadius())) {
					//std::cout << "Kolizja - wez sie odbij" << std::endl;
					sf::Vector2f normal = sf::Vector2f(
						(currentBallPosition.x - mainBallPosition.x) / distance,
						(currentBallPosition.y - mainBallPosition.y) / distance
					);
					float J =
						(balls[i].getMass() * balls[j].getMass()) /
						(balls[i].getMass() + balls[j].getMass())
						*(2) *
						dotProduct(balls[i].getVelocity() - balls[j].getVelocity(), normal);

					sf::Vector2f reflectVector1 = balls[i].getVelocity() - J / balls[i].getMass() * normal;
					balls[i].setVelocity(reflectVector1);
					balls[i].setLastTouchedIndex(j);

					sf::Vector2f reflectVector2 = balls[j].getVelocity() + J / balls[j].getMass() * normal;
					balls[j].setVelocity(reflectVector2);
					balls[j].setLastTouchedIndex(i);
				}
			}
		}
		for (int j = 0; j < walls.size(); j++) {

			float CircleX = balls[i].getPosition().x + balls[i].getRadius();
			float CircleY = balls[i].getPosition().y + balls[i].getRadius();
			float CircleRadius = balls[i].getRadius();

			float RectX = walls[j].getPosition().x;
			float RectY = walls[j].getPosition().y;
			float RectWidth = walls[j].getDimentions().x;
			float RectHeight = walls[j].getDimentions().y;


			float DeltaX = CircleX - std::max(RectX, std::min(CircleX, RectX + RectWidth));
			float DeltaY = CircleY - std::max(RectY, std::min(CircleY, RectY + RectHeight));
			if ((DeltaX * DeltaX + DeltaY * DeltaY) < (CircleRadius * CircleRadius)) {
				//std::cout << "Kolizja - wez sie odbij od sciany" << std::endl;


				sf::Vector2f nearestPoint(std::max(RectX, std::min(CircleX, RectX + RectWidth)), std::max(RectY, std::min(CircleY, RectY + RectHeight)));
				float distance = sqrt(pow(nearestPoint.x - CircleX, 2) + pow(nearestPoint.y - CircleY, 2));

				sf::Vector2f normal = sf::Vector2f(
					(CircleX - nearestPoint.x) / distance,
					(CircleY - nearestPoint.y) / distance
				);
				sf::Vector2f reflectVector1 = balls[i].getVelocity() - 2 * dotProduct(balls[i].getVelocity(), normal)*normal;
				
				balls[i].setVelocity(reflectVector1);
				balls[i].setLastTouchedIndex(i);
			}
		}
	}
}


// balls[i].getVelocity() - 2 * dotProduct*normal;