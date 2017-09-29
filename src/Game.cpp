#include "Game.hpp"
#include "physics.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Breakout"),
	//ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2) ,
	paddle{WINDOW_WIDTH/2, WINDOW_HEIGHT-50} {

    window.setFramerateLimit(60);
	srand(static_cast<int>(time(NULL)));

	// build wall
	for (int c{ 0 }; c < BLOCK_COLUMNS; ++c)
		for (int r{ 0 }; r < BLOCK_ROWS; ++r) {
			if (rand() % 5 == 0 && r > 0 && r < BLOCK_ROWS-1 && c > 0 && c < BLOCK_ROWS-1)
				balls.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
			else blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
		}

	// main ball
	balls.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, true);
	
}


void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
		if (!processEvents()) break;
		if (balls.size() <= 0) break;
		bool endGame = true;
		for (auto& ball : balls) if (ball.isActive) {
			endGame = false;
			break;
		}
		if (endGame) break;
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
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) return false;
    
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		paddle.veclocity.x = -PADDLE_VELOCITY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		paddle.veclocity.x = PADDLE_VELOCITY;
	else
		paddle.veclocity.x = 0;

    return true;
}

void Game::update(sf::Time deltaTime) {
    
	paddle.update(deltaTime);

	for (auto& ball : balls) {
		ball.update(deltaTime);
		testCollision(paddle, ball);
		for (auto& block : blocks) testCollision(block, ball);
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
		return ball.bottom() >= WINDOW_HEIGHT;
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


