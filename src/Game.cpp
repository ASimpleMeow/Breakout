#include "Game.hpp"
#include "physics.hpp"

#include <iostream>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Blockout"),
	paddle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50),
	gameLevel{ 1 },
	score{ 0 } {

    window.setFramerateLimit(60);
	view = window.getView();

	if (font.loadFromFile("media/font/trs-million.ttf")) {
		scoreText.setFont(font);
		scoreText.setCharacterSize(30);
		scoreText.setStyle(sf::Text::Underlined);
		scoreText.setString("");
	} else {
		std::cout << "Error reading font from media/font/\n";
		std::exit(-1);
	}

	init(gameLevel);
}

void Game::init(int level) {

	balls.clear();
	blocks.clear();
	score = 0;

	gameLevel = level;

	// main ball
	balls.emplace_back(windowWidth / 2, windowHeight / 2, true);

	//reset paddle
	paddle.shape.setPosition(windowWidth / 2, windowHeight - 50 );

	switch (gameLevel) {
	case 3:
		buildLevel([this](int c, int r){
			if (rand() % 5 == 0 && r > 0 && r < BLOCK_ROWS - 1 && c > 0 && c < BLOCK_COLUMNS - 1){
				balls.emplace_back((c + 1)*(BLOCK_WIDTH_RATIO*windowWidth + 3) + 22,
					(r + 2)*(BLOCK_HEIGHT_RATIO*windowHeight + 5));
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
			blocks.emplace_back((c + 1)*(BLOCK_WIDTH_RATIO*windowWidth + 3) + 22,
				(r + 2)*(BLOCK_HEIGHT_RATIO*windowHeight + 5), type);
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
			blocks.emplace_back((c + 1)*(BLOCK_WIDTH_RATIO*windowWidth + 3) + 22,
				(r + 2)*(BLOCK_HEIGHT_RATIO*windowHeight + 5));
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
			onResize();
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
	}

	blocks.erase(std::remove_if(std::begin(blocks), std::end(blocks),
		[this](const Block& block) {
		if (block.destroyed) score += static_cast<int>(block.blockType);
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

	scoreText.setString("Level : "+ std::to_string(gameLevel) +"\tScore : " + std::to_string(score));
}

void Game::render() {
    
    window.clear(sf::Color::Black);
    
	for(auto& ball: balls) window.draw(ball.shape);
	window.draw(paddle.shape);
	for (auto& block : blocks) window.draw(block.shape);
	window.draw(scoreText);

    window.display();
}

void Game::onResize() {
	sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());

	if (size.x < WINDOW_WIDTH) size.x = WINDOW_WIDTH;
	if (size.y < WINDOW_HEIGHT) size.y = WINDOW_HEIGHT;

	window.setSize(static_cast<sf::Vector2u>(size));
	view = sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y));
	window.setView(view);

	windowWidth = size.x;
	windowHeight = size.y;

	for (auto& ball : balls) ball.resize();
	for (auto& block : blocks) block.resize();
	paddle.resize();

}


