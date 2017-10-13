#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH{800}, WINDOW_HEIGHT{600};

constexpr float BALL_RADIUS{ 10.0f }, BALL_VELOCITY_MIN{ 135.0f }, BALL_VELOCITY_MAX{ 175.0f }, SLOWED_TIMER{ 5 };

struct Circle {
	sf::CircleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getRadius(); }
	float right() const noexcept { return x() + shape.getRadius(); }
	float top() const noexcept { return y() - shape.getRadius();  }
	float bottom() const noexcept { return y() + shape.getRadius();  }
};

constexpr float PADDLE_WIDTH{ 120.0f }, PADDLE_HEIGHT{ 20.0f }, PADDLE_VELOCITY{ 200.0f };

struct Rectangle {
	sf::RectangleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getSize().x/2.0f; }
	float right() const noexcept { return x() + shape.getSize().x/2.0f; }
	float top() const noexcept { return y() - shape.getSize().y/2.0f; }
	float bottom() const noexcept { return y() + shape.getSize().y/2.0f;  }
};

constexpr float BLOCK_WIDTH{60.0f}, BLOCK_HEIGHT{20.0f};
constexpr int BLOCK_COLUMNS{ 11 }, BLOCK_ROWS{ 5 };
constexpr int BLOCK_REGEN_TIMER{ 7 };

/*Reason for not using the enum class : 
	- I require the use of the int value (for block lives and score)
	- I have no other interfering enums */
enum BlockType {
	TRAP = 0,
	NORMAL = 1,
	REGEN = 2,
	DURABLE = 3
};

enum class GameType {
	NORMAL, AUTO_PADDLE, TRAPPED_BALLS, MULTI_BLOCKS
};
#endif

