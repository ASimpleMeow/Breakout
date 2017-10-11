#include "Ball.hpp"
#include <iostream>

Ball::Ball(float x, float y, bool active) : 
	isActive{active},
	spawn{x,y} 
{
	shape.setPosition({ x,y });
	shape.setRadius(BALL_RADIUS_RATIO * windowWidth);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin({ BALL_RADIUS_RATIO * windowWidth, BALL_RADIUS_RATIO * windowWidth });
	float randomVelocity = BALL_VELOCITY_MIN + (rand() % static_cast<int>(BALL_VELOCITY_MAX - BALL_VELOCITY_MIN + 1));
	velocity = { (rand() % 2 == 0) ? -randomVelocity : randomVelocity , (rand() % 2 == 0) ? -randomVelocity : randomVelocity };
}

void Ball::update(sf::Time deltaTime) {

	float randomVelocity = BALL_VELOCITY_MIN + (rand() % static_cast<int>(BALL_VELOCITY_MAX - BALL_VELOCITY_MIN + 1));

	shape.move( (slowed ? (velocity * 1.5f) : velocity) * deltaTime.asSeconds() * (float)(windowWidth / WINDOW_WIDTH));

	if (left() < 0) velocity.x = randomVelocity;
	else if (right() > windowWidth) velocity.x = -randomVelocity;

	if (top() < 0) velocity.y = randomVelocity;

	if (bottom() >= windowHeight) destroyed = true;

	if (slowed) {
		slowedTimer -= deltaTime.asSeconds();
		if (slowedTimer <= 0) {
			slowedTimer = SLOWED_TIMER;
			slowed = false;
		}
	}

	if (isActive) return;
	if (std::fabs(y() - spawn.y) > ((BLOCK_HEIGHT_RATIO*windowHeight)*BLOCK_ROWS)) isActive = true;
}

void Ball::resize() {
	shape.setRadius(BALL_RADIUS_RATIO * windowWidth);
	shape.setOrigin({ BALL_RADIUS_RATIO * windowWidth, BALL_RADIUS_RATIO * windowWidth });
}