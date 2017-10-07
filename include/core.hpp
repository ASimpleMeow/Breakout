#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH{800}, WINDOW_HEIGHT{600};
extern int CURRENT_WINDOW_WIDTH, CURRENT_WINDOW_HEIGHT;

constexpr float BALL_RADIUS_RATIO{ 0.0125f }, BALL_VELOCITY_MIN{ 135.0f }, BALL_VELOCITY_MAX{ 175.0f };
constexpr float SLOWED_TIMER{ 5 };

struct Circle {
	sf::CircleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getRadius(); }
	float right() const noexcept { return x() + shape.getRadius(); }
	float top() const noexcept { return y() - shape.getRadius();  }
	float bottom() const noexcept { return y() + shape.getRadius();  }
};

constexpr float PADDLE_WIDTH_RATIO{ 0.150f }, PADDLE_HEIGHT_RATIO{ 0.0333f };
constexpr float PADDLE_VELOCITY{ 200.0f };

struct Rectangle {
	sf::RectangleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getSize().x/2.0f; }
	float right() const noexcept { return x() + shape.getSize().x/2.0f; }
	float top() const noexcept { return y() - shape.getSize().y/2.0f; }
	float bottom() const noexcept { return y() + shape.getSize().y/2.0f;  }
};

constexpr float BLOCK_WIDTH_RATIO{ 0.0750f }, BLOCK_HEIGHT_RATIO{ 0.0333f };
constexpr int BLOCK_COLUMNS{ 11 }, BLOCK_ROWS{ 5 };
constexpr int BLOCK_REGEN_TIMER{ 7 };

enum BlockType {
	TRAP = 0,
	NORMAL = 1,
	REGEN = 2,
	DURABLE = 3
};
#endif

