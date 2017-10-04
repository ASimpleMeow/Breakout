#include "Game.hpp"
#include "physics.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Breakout"),
	paddle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50),
	gameLevel{1} {

    window.setFramerateLimit(60);

	srand(static_cast<int>(time(NULL)));

	init(gameLevel);
	
}

void Game::init(int level) {

	balls.clear();
	blocks.clear();

	gameLevel = level;

	// main ball
	balls.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, true);

	//reset paddle
	paddle.shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 );

	switch (gameLevel) {
	case 3:
		buildLevel([this](int c, int r){
			if (rand() % 5 == 0 && r > 0 && r < BLOCK_ROWS - 1 && c > 0 && c < BLOCK_ROWS - 1){
				balls.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
				return true;
			}
			return false;
		});
		break;
	case 4:
		buildLevel([this](int c, int r) {
			BlockType type{ NORMAL };
			switch (rand() % 5) {
			case 0:
				type = TRAP;
				break;
			case 1:
				type = DURABLE;
				break;
			case 2:
				type = REGEN;
				break;
			}
			blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5), type);
			return true;
		});
		break;
	default:
		buildLevel([](int c, int r) {return false; });
		break;
	}
}

void Game::buildLevel(std::function<bool(int,int)> func){
	for (int c{ 0 }; c < BLOCK_COLUMNS; ++c)
		for (int r{ 0 }; r < BLOCK_ROWS; ++r) {
			if (func(c, r)) continue;
			blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
		}
}


void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
		if (!processEvents()) break;
		/*if (balls.size() <= 0) break;
		bool endGame = true;
		for (auto& ball : balls) if (ball.isActive) {
			endGame = false;
			break;
		}
		if (endGame) break;*/
        update(clock.restart());
        render();
    }
}


bool Game::processEvents() {
    
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
            break;
		} else if (event.type == sf::Event::Resized) {
			sf::Vector2u keepSize = { (sf::Uint32)WINDOW_WIDTH, (sf::Uint32)WINDOW_HEIGHT };
			window.setSize(keepSize);
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) return false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) init(1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) init(2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) init(3);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) init(4);
    

	if (gameLevel == 2) return true;	//automatic paddle

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		paddle.veclocity.x = -PADDLE_VELOCITY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		paddle.veclocity.x = PADDLE_VELOCITY;
	else
		paddle.veclocity.x = 0;

    return true;
}

void Game::update(sf::Time deltaTime) {
    
	if (gameLevel == 2) paddle.update(deltaTime, balls[0].x());
	else paddle.update(deltaTime);
	

	for (auto& ball : balls) {
		ball.update(deltaTime);
		testCollision(paddle, ball);
		for (auto& block : blocks) {
			testCollision(block, ball);
			block.update(deltaTime);
		}
		if (!ball.isActive) {
			if (std::fabs(ball.y() - ball.spawn.y) > ball.shape.getRadius() * 5)
				ball.isActive = true;
		}
	}

	blocks.erase(std::remove_if(std::begin(blocks), std::end(blocks),
		[](const Block& block) {
		return block.destroyed;
		}
		), std::end(blocks)
	);

	balls.erase(std::remove_if(std::begin(balls), std::end(balls),
		[](const Ball& ball) {
		return ball.destroyed;
		}
		), std::end(balls)
	);

}

void Game::render() {
    
    window.clear(sf::Color::Black);
    
	for(auto& ball: balls) window.draw(ball.shape);
	window.draw(paddle.shape);
	for (auto& block : blocks) window.draw(block.shape);

    window.display();
}


