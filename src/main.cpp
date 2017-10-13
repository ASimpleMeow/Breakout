#include "Game.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]) {

	srand(static_cast<int>(time(NULL)));

	Game game;
	game.run();
	
	return 0; 
}