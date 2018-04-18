//
//  Main.cpp
//  Game-mac
//


#include "Game.h"

int main(int argc, char** argv)
{
	// TODO
    Game game;

	//Parse multiplayer parameters;
	//usage: 0 1 1 localhsot
	if (argc > 2) {
		game.mp_isGuest = (int)argv[1];
		if (game.mp_isGuest == 0) {
			game.mp_gameID = (int)argv[2];
			game.mp_userID = (int)argv[3];
			game.mp_svrIP = argv[4];
		}
	}
    if (game.Initialize()){
        game.RunLoop();
    }
    game.Shutdown();
	return 0;
}
