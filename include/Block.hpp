#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "core.hpp"

struct Block : public Rectangle{

	bool destroyed{ false };
	sf::Vector2f positionRatio;
	int health;
	float regenTimer{ BLOCK_REGEN_TIMER };
	BlockType blockType;

	Block(float x, float y, BlockType type = BlockType::NORMAL);

	void update(sf::Time deltaTime);
	void resize();

};

#endif // !BLOCK_HPP
