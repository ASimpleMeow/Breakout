#include "Ball.hpp"

Ball::Ball(float x, float y, bool active) : 
	isActive{active},
	spawn{x,y} 
{
	shape.setPosition({ x,y });
	shape.setRadius(BALL_RADIUS);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin({ BALL_RADIUS, BALL_RADIUS });
}

void Ball::update(sf::Time deltaTime) {
	shape.move( (slowed ? (velocity * 1.5f) : velocity) * deltaTime.asSeconds());

	if (left() < 0) {
		velocity.x = BALL_VELOCITY;
	} else if (right() > WINDOW_WIDTH) {
		velocity.x = -BALL_VELOCITY;
	}

	if (top() < 0) {
		velocity.y = BALL_VELOCITY;
	} else if (bottom() > WINDOW_HEIGHT) {
		velocity.y = -BALL_VELOCITY;
	}

	if (bottom() >= WINDOW_HEIGHT) destroyed = true;

	if (slowed) {
		slowedTimer -= deltaTime.asSeconds();
		if (slowedTimer <= 0) {
			slowedTimer = SLOWED_TIMER;
			slowed = false;
		}
	}
}