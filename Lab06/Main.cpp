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
	/*if (argc > 2) {
	game.mp_isGuest = (int)argv[1];
	if (game.mp_isGuest == 0) {
	game.mp_gameName = argv[2];
	game.mp_yourUserID = (int)argv[3];
	game.mp_friendUserID = (int)argv[4];
	game.mp_svrIP = argv[5];
	}
	}*/
	game.mp_isGuest = 0;
	game.mp_gameName = "test222";
	game.mp_yourUserID = 1;
	game.mp_friendUserID = 2;
	game.mp_svrIP = "192.168.43.67";
    if (game.Initialize()){
        game.RunLoop();
    }
    game.Shutdown();
	return 0;
}
