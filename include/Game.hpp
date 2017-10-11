#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <functional>

#include "core.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"

class Game {
public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    Game();
    void run();
    
private:
    bool processEvents();
    void update(sf::Time deltaTime);
    void render();
	void onResize();
	void init(int level);

	void buildLevel(std::function<bool(int, int)> func);
    
	int gameLevel;

    sf::RenderWindow window; 
	sf::View view;
	sf::Text scoreText;
	sf::Font font;
    
    // game specific code
	std::vector<Ball> balls;
	Paddle paddle;
	std::vector<Block> blocks;
	unsigned int score;

};
#endif