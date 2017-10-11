#include "Block.hpp"

#include "core.hpp"
#include <iostream>


Block::Block(float x, float y, BlockType type) {
	shape.setPosition({ x,y });
	shape.setSize({ BLOCK_WIDTH_RATIO * windowWidth, BLOCK_HEIGHT_RATIO * windowHeight });
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin({ (BLOCK_WIDTH_RATIO * windowWidth) / 2, (BLOCK_HEIGHT_RATIO * windowHeight) / 2 });
	blockType = type;
	positionRatio = {x/WINDOW_WIDTH, y/WINDOW_HEIGHT};

	switch (blockType) {
	case DURABLE:
		health = DURABLE;
		shape.setFillColor(sf::Color::White);
		break;
	case REGEN:
		shape.setFillColor(sf::Color::Blue);
		health = REGEN;
		break;
	case TRAP:
		shape.setFillColor(sf::Color::Red);
	default:
		health = NORMAL;
		break;
	}
}

void Block::update(sf::Time deltaTime) {

	if (health <= 0) {
		destroyed = true;
		return;
	}

	int damageScale = 255;

	switch (blockType) {
	case DURABLE:
		damageScale = 255 - static_cast<int>((health - DURABLE) / -0.015f);
		shape.setFillColor(sf::Color( damageScale, damageScale, damageScale));
		break;
	case REGEN:
		if (health > 0 && health < REGEN) {
			regenTimer -= deltaTime.asSeconds();
			shape.setFillColor(sf::Color( 165, 200, 255 ));

			if (regenTimer <= 0) {
				health = ((health + 1) >= REGEN) ? REGEN : health + 1;
				shape.setFillColor(sf::Color::Blue);
				regenTimer = BLOCK_REGEN_TIMER;
			}
		}
		break;
	}
}

void Block::resize() {
	shape.setPosition({ positionRatio.x * windowWidth, positionRatio.y * windowHeight });
	shape.setSize({ BLOCK_WIDTH_RATIO * windowWidth, BLOCK_HEIGHT_RATIO * windowHeight });
	shape.setOrigin({ (BLOCK_WIDTH_RATIO * windowWidth) / 2, (BLOCK_HEIGHT_RATIO * windowHeight) / 2 });
}