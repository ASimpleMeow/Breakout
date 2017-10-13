#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <functional>
#include <SFML\Audio.hpp>

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
	void onResize(int width, int height);
	void init(GameType gameType);

	void buildLevel(std::function<bool(int, int)> func);
    
	GameType gameLevel;

    sf::RenderWindow window; 
	sf::View view;
	sf::Text scoreText;
	sf::Font font;
	sf::Music music;
    
    // game specific code
	std::vector<Ball> balls;
	Paddle paddle;
	std::vector<Block> blocks;
	unsigned int score;

};
#endif