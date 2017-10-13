#include "Game.hpp"
#include "physics.hpp"

#include <iostream>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Blockout"),
	view(window.getView()),
	paddle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50),
	gameLevel{ GameType::NORMAL },
	score{ 0 } {

    window.setFramerateLimit(60);

	if (music.openFromFile("media/music/music.ogg")) {
		music.setVolume(50);
		music.setLoop(true);
		music.play();
	} else {
		std::cout << "Error reading font from media/music - needs music.mid file\n";
	}

	if (font.loadFromFile("media/font/trs-million.ttf")) {
		scoreText.setFont(font);
		scoreText.setCharacterSize(30);
		scoreText.setStyle(sf::Text::Underlined);
		scoreText.setString("");
	} else {
		std::cout << "Error reading font from media/font/ - needs trs-million.ttf font\n";
	}

	init(gameLevel);
}

void Game::init(GameType gameType) {

	balls.clear();
	blocks.clear();
	score = 0;

	gameLevel = gameType;

	// main ball
	balls.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, true);

	//reset paddle
	paddle.shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 );

	switch (gameLevel) {
	case GameType::TRAPPED_BALLS:
		buildLevel([this](int c, int r){
			if (rand() % 5 == 0 && r > 0 && r < BLOCK_ROWS - 1 && c > 0 && c < BLOCK_COLUMNS - 1){
				balls.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22,
					(r + 2)*(BLOCK_HEIGHT + 5));
				return true;
			}
			return false;
		});
		break;
	case GameType::MULTI_BLOCKS:
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
			blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22,
				(r + 2)*(BLOCK_HEIGHT + 5), type);
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
			blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22,
				(r + 2)*(BLOCK_HEIGHT + 5));
		}
}


void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
		if (!processEvents()) break;
        update(clock.restart());
        render();
    }
	try {
		music.stop();
	} catch (const char* msg) {

	}
}


bool Game::processEvents() {
    
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
            break;
		} else if (event.type == sf::Event::Resized) {
			onResize(event.size.width, event.size.height);
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) return false;

	// Levels
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) init(GameType::NORMAL);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) init(GameType::AUTO_PADDLE);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) init(GameType::TRAPPED_BALLS);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) init(GameType::MULTI_BLOCKS);
    

	if (gameLevel == GameType::AUTO_PADDLE) return true;	// Automatic paddle

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		paddle.veclocity.x = -PADDLE_VELOCITY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		paddle.veclocity.x = PADDLE_VELOCITY;
	else
		paddle.veclocity.x = 0;

    return true;
}

void Game::update(sf::Time deltaTime) {

	auto gameEnd = [](std::vector<Ball>& balls) {
		for (auto& ball : balls) if (ball.isActive) return false;
		return true;
	};
	if (gameEnd(balls) || balls.size() == 0) init(gameLevel);
    
	if (gameLevel == GameType::AUTO_PADDLE) paddle.update(deltaTime, balls[0].x());
	else paddle.update(deltaTime);
	

	for (auto& ball : balls) {
		ball.update(deltaTime);
		testCollision(paddle, ball);
		for (auto& block : blocks) {
			testCollision(block, ball);
			block.update(deltaTime);
			if(block.destroyed) score += static_cast<int>(block.blockType);
		}
	}
	
	auto eraseFromVector = [](auto& objects) {
		objects.erase(std::remove_if(std::begin(objects), std::end(objects),
			[](const auto& object) {
			return object.destroyed;
			}), std::end(objects)
		);
	};
	eraseFromVector(blocks);
	eraseFromVector(balls);

	scoreText.setString("Level : "+ std::to_string(static_cast<int>(gameLevel)+1) +"\tScore : " + std::to_string(score));
	if (blocks.empty()) {
		int level = static_cast<int>(gameLevel);
		level = ++level % 4;
		init(static_cast<GameType>(level));
	}
}

void Game::render() {
    
    window.clear(sf::Color::Black);
    
	for(auto& ball: balls) window.draw(ball.shape);
	window.draw(paddle.shape);
	for (auto& block : blocks) window.draw(block.shape);
	window.draw(scoreText);

    window.display();
}

/*Heavily influenced by SFML's example on resizing*/
void Game::onResize(int width, int height) {
	
	float windowRatio{ (float)width / (float)height };
	float viewRatio{ (float)view.getSize().x / (float)view.getSize().y };
	sf::Vector2f size{ 1,1 };
	sf::Vector2f position{ 0,0 };

	bool spacing = (windowRatio < viewRatio) ? false : true;

	if (spacing) {
		size.x = viewRatio / windowRatio;
		position.x = (1 - size.x) / 2.0f;
	} else {
		size.y = windowRatio / viewRatio;
		position.y = (1 - size.y) / 2.0f;
	}

	view.setViewport(sf::FloatRect(position, size));
	window.setView(view);
}


