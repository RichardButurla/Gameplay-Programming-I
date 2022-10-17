//Richard Buturla
//C00272345
//03/10/2022
#include "../include/Game.h"



int main()
{
	std::srand(static_cast<unsigned int>(time(0))); //seed for generation
	Game game;
	
	game.run();

	return 0;
}