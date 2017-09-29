#ifndef BRICK_HPP
#define BRICK_HPP

#include "core.hpp"

struct Block : public Rectangle {

	bool destroyed{ false };

	Block(float x, float y);

};

#endif // !BRICK_HPP
