#include "Paddle.hpp"

Paddle::Paddle(float x, float y) {
	shape.setPosition({ x,y });
	shape.setSize({PADDLE_WIDTH_RATIO * CURRENT_WINDOW_WIDTH, PADDLE_HEIGHT_RATIO * CURRENT_WINDOW_HEIGHT});
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin({ (PADDLE_WIDTH_RATIO * CURRENT_WINDOW_WIDTH)/2, (PADDLE_HEIGHT_RATIO * CURRENT_WINDOW_HEIGHT)/2 });
}

void Paddle::update(sf::Time deltaTime) {

	shape.move(veclocity * deltaTime.asSeconds());

	if (left() < 0) shape.move(-left(), 0);
	if (right() > CURRENT_WINDOW_WIDTH) shape.move(-right() + CURRENT_WINDOW_WIDTH, 0);
}

void Paddle::update(sf::Time deltaTime, float ballX) {
	update(deltaTime);

	if (ballX > x()) veclocity.x = PADDLE_VELOCITY;
	else if (ballX < x()) veclocity.x = -PADDLE_VELOCITY;
	else veclocity.x = 0;
}

void Paddle::resize() {
	shape.setSize({ PADDLE_WIDTH_RATIO * CURRENT_WINDOW_WIDTH, PADDLE_HEIGHT_RATIO * CURRENT_WINDOW_HEIGHT });
	shape.setOrigin({ (PADDLE_WIDTH_RATIO * CURRENT_WINDOW_WIDTH) / 2, (PADDLE_HEIGHT_RATIO * CURRENT_WINDOW_HEIGHT) / 2 });
}