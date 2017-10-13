#ifndef BALL_HPP
#define BALL_HPP

#include "core.hpp"

struct Ball : public Circle {
	
	bool destroyed{ false };
	bool slowed{ false };
	sf::Vector2f velocity;
	sf::Vector2f spawn;

	bool isActive;
	float slowedTimer{SLOWED_TIMER};

	Ball(float x, float y, bool active = false);

	void update(sf::Time deltaTime);
};

#endif // !BALL_HPP

