//
//  Main.cpp
//  Game-mac
//


#include "Game.h"

int main(int argc, char** argv)
{
	// TODO
    Game game;
    if (game.Initialize()){
        game.RunLoop();
    }
    game.Shutdown();
	return 0;
}
