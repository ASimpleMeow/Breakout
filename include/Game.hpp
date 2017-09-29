#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

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
    
    sf::RenderWindow window;
    
    // game specific code
	//Ball ball;
	std::vector<Ball> balls;
	Paddle paddle;
	std::vector<Block> blocks;

};
#endif