#include "Paddle.hpp"

Paddle::Paddle(float x, float y) {
	shape.setPosition({ x,y });
	shape.setSize({PADDLE_WIDTH_RATIO * windowWidth, PADDLE_HEIGHT_RATIO * windowHeight});
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin({ (PADDLE_WIDTH_RATIO * windowWidth)/2, (PADDLE_HEIGHT_RATIO * windowHeight)/2 });
	positionRatio = { x / WINDOW_WIDTH, y / WINDOW_HEIGHT };
}

void Paddle::update(sf::Time deltaTime) {

	shape.move(veclocity * deltaTime.asSeconds());

	if (left() < 0) shape.move(-left(), 0);
	if (right() > windowWidth) shape.move(-right() + windowWidth, 0);
}

void Paddle::update(sf::Time deltaTime, float ballX) {
	update(deltaTime);

	if (ballX > x()) veclocity.x = PADDLE_VELOCITY;
	else if (ballX < x()) veclocity.x = -PADDLE_VELOCITY;
	else veclocity.x = 0;
}

void Paddle::resize() {
	shape.setPosition({ shape.getPosition().x, positionRatio.y * windowHeight });
	shape.setSize({ PADDLE_WIDTH_RATIO * windowWidth, PADDLE_HEIGHT_RATIO * windowHeight });
	shape.setOrigin({ (PADDLE_WIDTH_RATIO * windowWidth) / 2, (PADDLE_HEIGHT_RATIO * windowHeight) / 2 });
}