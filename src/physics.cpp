#include "core.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "physics.hpp"

#include <cmath>

void testCollision(const Paddle& paddle, Ball& ball) noexcept {
	if (!isIntersecting(paddle, ball)) return;

	float randomVelocity = BALL_VELOCITY_MIN + (rand() % static_cast<int>(BALL_VELOCITY_MAX - BALL_VELOCITY_MIN + 1));

	//if (!ball.isActive) ball.isActive = true;

	ball.velocity.y = -randomVelocity;
	ball.velocity.x = (ball.x() < paddle.x()) ? -randomVelocity : randomVelocity;
}


void testCollision(Block& block, Ball& ball) noexcept {
	if (!isIntersecting(block, ball)) return;

	if (ball.isActive) block.health--;
	if (block.blockType == TRAP) ball.slowed = true;

	float overlapLeft{ ball.right() - block.left() };
	float overlapRight{ block.right() - ball.left() };
	float overlapTop{ ball.bottom() - block.top() };
	float overlapBottom{ block.bottom() - ball.top() };

	bool ballFromLeft(fabs(overlapLeft) < fabs(overlapRight));
	bool ballFromTop(fabs(overlapTop) < fabs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };
	float randomVelocity = BALL_VELOCITY_MIN + (rand() % static_cast<int>(BALL_VELOCITY_MAX - BALL_VELOCITY_MIN + 1));

	if (fabs(minOverlapX) < fabs(minOverlapY)) ball.velocity.x = ballFromLeft ? -randomVelocity : randomVelocity;
	else ball.velocity.y = ballFromTop ? -randomVelocity : randomVelocity;
	
}