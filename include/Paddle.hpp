#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "core.hpp"


struct Paddle : Rectangle {

	sf::Vector2f veclocity;
	sf::Vector2f positionRatio;

	Paddle(float x, float y);

	void update(sf::Time deltaTime);
	void update(sf::Time deltaTime, float ballX);
	void resize();
};

#endif // !PADDLE_HPP

