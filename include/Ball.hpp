#ifndef BALL_HPP
#define BALL_HPP

#include "core.hpp"

struct Ball : public Circle {
	
	bool destroyed{ false };
	bool slowed{ false };
	sf::Vector2f velocity{ -BALL_VELOCITY_MIN, -BALL_VELOCITY_MIN };
	sf::Vector2f spawn;

	bool isActive;
	float slowedTimer{SLOWED_TIMER};

	Ball(float x, float y, bool active = false);

	void update(sf::Time deltaTime);
	void resize();
};

#endif // !BALL_HPP

