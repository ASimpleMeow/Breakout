#include "Ball.hpp"

Ball::Ball(float x, float y, bool active) : 
	isActive{active},
	spawn{x,y} 
{
	shape.setPosition({ x,y });
	shape.setRadius(BALL_RADIUS_RATIO * CURRENT_WINDOW_WIDTH);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin({ BALL_RADIUS_RATIO * CURRENT_WINDOW_WIDTH, BALL_RADIUS_RATIO * CURRENT_WINDOW_WIDTH });
}

void Ball::update(sf::Time deltaTime) {
	shape.move( (slowed ? (velocity * 1.5f) : velocity) * deltaTime.asSeconds());

	if (left() < 0) velocity.x = BALL_VELOCITY_MIN;
	else if (right() > CURRENT_WINDOW_WIDTH) velocity.x = -BALL_VELOCITY_MIN;

	if (top() < 0) velocity.y = BALL_VELOCITY_MIN;

	if (bottom() >= CURRENT_WINDOW_HEIGHT) destroyed = true;

	if (slowed) {
		slowedTimer -= deltaTime.asSeconds();
		if (slowedTimer <= 0) {
			slowedTimer = SLOWED_TIMER;
			slowed = false;
		}
	}

	if (isActive) return;
	if (std::fabs(y() - spawn.y) > ((BLOCK_HEIGHT_RATIO*CURRENT_WINDOW_HEIGHT)*BLOCK_ROWS)) isActive = true;
}

void Ball::resize() {
	shape.setRadius(BALL_RADIUS_RATIO * CURRENT_WINDOW_WIDTH);
	shape.setOrigin({ BALL_RADIUS_RATIO * CURRENT_WINDOW_WIDTH, BALL_RADIUS_RATIO * CURRENT_WINDOW_WIDTH });
}