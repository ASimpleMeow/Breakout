#include "core.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "physics.hpp"

#include <cmath>

void testCollision(const Paddle& paddle, Ball& ball) noexcept {
	if (!isIntersecting(paddle, ball)) return;

	if (!ball.isActive) ball.isActive = true;

	ball.velocity.y = -BALL_VELOCITY;
	if (ball.x() < paddle.x()) {
		ball.velocity.x = -BALL_VELOCITY;
	} else {
		ball.velocity.x = BALL_VELOCITY;
	}
}


void testCollision(Block& block, Ball& ball) noexcept {
	if (!isIntersecting(block, ball)) return;

	if (ball.isActive) block.health--;
	if (block.blockType == TRAP) {
		ball.slowed = true;
		return;
	}


	float overlapLeft{ ball.right() - block.left() };
	float overlapRight{ block.right() - ball.left() };
	float overlapTop{ ball.bottom() - block.top() };
	float overlapBottom{ block.bottom() - ball.top() };

	bool ballFromLeft(fabs(overlapLeft) < fabs(overlapRight));
	bool ballFromTop(fabs(overlapTop) < fabs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (fabs(minOverlapX) < fabs(minOverlapY)) {
		ball.velocity.x = ballFromLeft ? -BALL_VELOCITY : BALL_VELOCITY;
	} else {
		ball.velocity.y = ballFromTop ? -BALL_VELOCITY : BALL_VELOCITY;
	}
	
}