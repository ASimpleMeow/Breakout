#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "core.hpp"


struct Paddle : Rectangle {

	sf::Vector2f veclocity;

	Paddle(float x, float y);

	void update(sf::Time deltaTime);
	void update(sf::Time deltaTime, float ballX);
};

#endif // !PADDLE_HPP

