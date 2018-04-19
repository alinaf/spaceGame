#pragma once

// TODO
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "SpriteComponent.h"
#include "Block.h"
#include "Player.h"
#include "Barrel.h"
#include "BarrelSpawner.h"
#include "SDL/SDL_mixer.h"
#include "Background.h"
#include "Coin.h"
#include "AnimatedSprite.h"
#include "SpeedBoost.h"
#include "Invulnerability.h"
#include "MoonBounce.h"
#include "DoubleCoin.h"

#include "mysql.h"
#pragma comment(lib, "libmysql")
#pragma comment(lib, "mysqlclient")

class Actor;


class Game{
public:
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void AddSprite(SpriteComponent* sc);
    void RemoveSprite(SpriteComponent* sc);
    SDL_Texture* GetTexture(const char* filename);
    std::vector<Block*> & GetBlocks() {return blocks;}
    Player* GetPlayer() const{return mPlayer;}
    Mix_Chunk* GetSound(const std::string& filename);
    Vector2 GetPlayerStart() const{return playerStart;}
    const Vector2& GetCameraPos() const {return mCameraPos;};
    void SetCameraPos(const Vector2& cameraPos);
    void LoadNextLevel();
    int numLevels;

    void AddScore(int num) {score += num;}
	int GetScore() { return score; }
	int GetOpponentScore() { return opponentScore; }
	void SetOpponentScore(int newScore) { opponentScore = newScore; }

	int mp_isGuest;
	int mp_yourUserID;
	int mp_friendUserID;
	std::string mp_gameName;
	std::string mp_svrIP;

	MYSQL *connection, mysql;
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int WALL_THICKNESS;
    int PADDLE_HEIGHT;
    bool quit;
    std::vector<Actor*> actors;
    SDL_Point speed;
    Uint32 prevTime;
    int dir;
    SDL_Texture* texture;
    std::unordered_map<std::string, SDL_Texture*> hashmap;
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    void LoadTexture(const char* filename);
    std::vector<SpriteComponent*> mSprites;
    std::vector<Block*> blocks;
    Player* mPlayer;
    void LoadSound(const std::string& filename);
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    Vector2 playerStart;
    Vector2 mCameraPos;
    int levelIndex;
    int score = 0;
	int opponentScore = 0;
    int mult = 1;
};
