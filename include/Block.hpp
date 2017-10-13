#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "core.hpp"

struct Block : public Rectangle{

	bool destroyed{ false };
	int health;
	float regenTimer{ BLOCK_REGEN_TIMER };
	BlockType blockType;

	Block(float x, float y, BlockType type = BlockType::NORMAL);

	void update(sf::Time deltaTime);
};

#endif // !BLOCK_HPP
