#include "Ball.hpp"

Ball::Ball(float x, float y, bool active) : 
	isActive{active},
	spawn{x,y} 
{
	shape.setPosition({ x,y });
	shape.setRadius(BALL_RADIUS_RATIO * windowWidth);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin({ BALL_RADIUS_RATIO * windowWidth, BALL_RADIUS_RATIO * windowWidth });
}

void Ball::update(sf::Time deltaTime) {
	shape.move( (slowed ? (velocity * 1.5f) : velocity) * deltaTime.asSeconds());

	if (left() < 0) velocity.x = BALL_VELOCITY_MIN;
	else if (right() > windowWidth) velocity.x = -BALL_VELOCITY_MIN;

	if (top() < 0) velocity.y = BALL_VELOCITY_MIN;

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