#include "Game.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CURRENT_WINDOW_WIDTH = WINDOW_WIDTH;
int CURRENT_WINDOW_HEIGHT = WINDOW_HEIGHT;

int main(int argc,char* argv[]) {

	srand(static_cast<int>(time(NULL)));

	Game game;
	game.run();
	
	return 0; 
}