#ifndef BALL_HPP
#define BALL_HPP

#include "core.hpp"

struct Ball : public Circle {
	
	sf::Vector2f velocity{ -BALL_VELOCITY, -BALL_VELOCITY };
	sf::Vector2f spawn;

	bool isActive;

	Ball(float x, float y, bool active = false);

	void update(sf::Time deltaTime);

};

#endif // !BALL_HPP

