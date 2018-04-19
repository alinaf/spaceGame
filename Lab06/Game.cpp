//
//  Game.cpp
//  Game-mac
//


#include "Game.h"
#include "Actor.h"
#include "SDL/SDL_image.h"
#include <fstream>
#include <iostream>
#include <string>
#include "PlayerMove.h"
#include "mysql.h"
#pragma comment(lib, "libmysql")
#pragma comment(lib, "mysqlclient")
using namespace std;

Game::Game(){
    quit = true;
    WALL_THICKNESS = 15;
    PADDLE_HEIGHT = 100;
    mPlayer = nullptr;
    levelIndex = 0;
    numLevels = 0;
}

void Game::AddActor(Actor* actor){
    actors.push_back(actor);
}

void Game::RemoveActor(Actor* actor){
    std::vector<Actor*>::iterator it = std::find(actors.begin(), actors.end(),actor);
    actors.erase(it);
}

void Game::AddSprite(SpriteComponent* sc){
    mSprites.push_back(sc);
    std::sort(mSprites.begin(), mSprites.end(), [](SpriteComponent* a, SpriteComponent* b){return a->GetDrawOrder()<b->GetDrawOrder();});
}

void Game::RemoveSprite(SpriteComponent* sc){
    std::vector<SpriteComponent*>::iterator it = std::find(mSprites.begin(), mSprites.end(), sc);
    mSprites.erase(it);
}

void Game::LoadTexture(const char* filename){
    SDL_Surface* surface = IMG_Load(filename);
    std::string fn(filename);
    hashmap[fn] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

SDL_Texture* Game::GetTexture(const char* filename){
    std::string fn(filename);
    return hashmap.find(fn)->second;
}

void Game::LoadSound(const std::string& filename){
    
	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    sounds[filename] = sound;

	if (filename == "Assets/Music/LastParadise.wav") {
		Mix_VolumeChunk(sound, 30);
	}
	else if (filename == "Assets/Sounds/PowerUp.wav") {
		Mix_VolumeChunk(sound, 70);
	} 
	else if (filename == "Assets/Sounds/PowerDown.wav") {
		Mix_VolumeChunk(sound, 90);
	}
	else if (filename == "Assets/Player/Falling.wav") {
		Mix_VolumeChunk(sound, 60);
	}
	else if (filename == "Assets/Player/Scream.wav") {
		Mix_VolumeChunk(sound, 60);
	}
	else if (filename == "Assets/Player/Jump.wav") {
		Mix_VolumeChunk(sound, 30);
	}
	else if (filename == "Assets/Crystal/Crystal.wav") {
		Mix_VolumeChunk(sound, 30);
	}
    else if (filename == "Assets/Sounds/Gravity.wav") {
        Mix_VolumeChunk(sound, 40);
    }
    else if (filename == "Assets/Sounds/explosion.wav"){
        Mix_VolumeChunk(sound, 10);
    }
    else if (filename == "Assets/Sounds/Coin_up.wav"){
        Mix_VolumeChunk(sound, 50);
    }
    else if (filename == "Assets/Sounds/Invincibility.wav"){
        Mix_VolumeChunk(sound, 30);
    }
}

Mix_Chunk* Game::GetSound(const std::string& filename){
    return sounds.find(filename)->second;
}

void Game::SetCameraPos(const Vector2& cameraPos){
    mCameraPos = cameraPos;
}

void Game::LoadData(){
    LoadTexture("Assets/Background.png");
    LoadTexture("Assets/Player/Idle.png");
    LoadTexture("Assets/BlockA.png");
    LoadTexture("Assets/BlockB.png");
    LoadTexture("Assets/BlockC.png");
    LoadTexture("Assets/BlockD.png");
    LoadTexture("Assets/BlockE.png");
    LoadTexture("Assets/BlockF.png");
    LoadTexture("Assets/Barrel.png");
    LoadTexture("Assets/Background/Sky_0.png");
    LoadTexture("Assets/Background/Sky_1.png");
    LoadTexture("Assets/Background/Sky_2.png");
    LoadTexture("Assets/Background/Mid_0.png");
    LoadTexture("Assets/Background/Mid_1.png");
    LoadTexture("Assets/Background/Mid_2.png");
	LoadTexture("Assets/Background/Fore_0.png");
    LoadTexture("Assets/Background/Fore_1.png");
    LoadTexture("Assets/Background/Fore_2.png");
    LoadTexture("Assets/doge.png");
    LoadTexture("Assets/gameover.png");
    
    for (int i = 1; i < 17; i++){
        std::string filename = "Assets/Crystal/crystal" + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 11; i++){
        std::string filename = "Assets/Player/Run" + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 11; i++){
        std::string filename = "Assets/Player/Rainbow" + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 7; i++){
        std::string filename = "Assets/Red/frame " + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 7; i++){
        std::string filename = "Assets/Yellow/frame " + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 7; i++){
        std::string filename = "Assets/Green/frame " + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 7; i++){
        std::string filename = "Assets/Blue/frame " + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 7; i++){
        std::string filename = "Assets/Yellow/frame " + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 12; i++){
        std::string filename = "Assets/glitch_meteor/meteor000" + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
    for (int i = 1; i < 11; i++){
        std::string filename = "Assets/Bubble_Explo/bubble_explo" + std::to_string(i) + ".png";
        LoadTexture(filename.c_str());
    }
    
	LoadSound("Assets/Music/LastParadise.wav");
	LoadSound("Assets/Sounds/PowerUp.wav");
	LoadSound("Assets/Sounds/PowerDown.wav");
    LoadSound("Assets/Sounds/Gravity.wav");
	LoadSound("Assets/Player/Falling.wav");
	LoadSound("Assets/Player/Scream.wav");
	LoadSound("Assets/Player/Jump.wav");
	LoadSound("Assets/Crystal/Crystal.wav");
    LoadSound("Assets/Sounds/explosion.wav");
    LoadSound("Assets/Sounds/Coin_up.wav");
    LoadSound("Assets/Sounds/Invincibility.wav");


	Actor* sky = new Actor(this);
    Actor* mid = new Actor(this);
    Actor* fore = new Actor(this);
    
    Background* bc1 = new Background(sky, 1);
    bc1->mParallax = 0.25f;
    bc1->AddImage(GetTexture("Assets/Background/Sky_0.png"));
    bc1->AddImage(GetTexture("Assets/Background/Sky_1.png"));
    bc1->AddImage(GetTexture("Assets/Background/Sky_2.png"));
    
    Background* bc2 = new Background(mid, 2);
    bc2->mParallax = 0.5f;
    bc2->AddImage(GetTexture("Assets/Background/Mid_0.png"));
    bc2->AddImage(GetTexture("Assets/Background/Mid_1.png"));
    bc2->AddImage(GetTexture("Assets/Background/Mid_2.png"));
    
    Background* bc3 = new Background(fore, 3);
    bc3->mParallax = 0.75f;
    bc3->AddImage(GetTexture("Assets/Background/Fore_0.png"));
    bc3->AddImage(GetTexture("Assets/Background/Fore_1.png"));
    bc3->AddImage(GetTexture("Assets/Background/Fore_2.png"));

    sky->SetSprite(bc1);
    sky->SetPosition(Vector2(0.0f, 384.0f));
    
    mid->SetSprite(bc2);
    mid->SetPosition(Vector2(0.0f, 384.0f));
    
    fore->SetSprite(bc3);
    fore->SetPosition(Vector2(0.0f, 384.0f));
    
    LoadNextLevel();
}

void Game::LoadNextLevel(){
    if (levelIndex > 5){
        levelIndex = 0;
    }
    std::string filename = "Assets/level" + std::to_string(levelIndex) + ".txt";
    std::ifstream ifile(filename.c_str());
    int x = 32 + numLevels*56*64;
    int y = 16;
    std::string curr;
    while (ifile>>curr){
        for (char a : curr){
            if (a!='.'){
                if (a=='P'){
                    if (mPlayer == nullptr){
                        Player* p = new Player(this);
                        mPlayer = p;
                        AnimatedSprite* as = new AnimatedSprite(p);
                        for (int i = 1; i < 11; i++){
                            std::string filename = "Assets/Player/Run" + std::to_string(i) + ".png";
                            as->AddImage(GetTexture(filename.c_str()));
                        }
                        p->SetSprite(as);
                        p->SetPosition(Vector2(x, y));
                        playerStart = Vector2(x, y);
                    }
                }
                else if (a=='O'){
                    BarrelSpawner* b = new BarrelSpawner(this);
                    b->SetPosition(Vector2(x, y));
                }
                else if (a=='*'){
                    Coin* c = new Coin(this);
                    AnimatedSprite* as = new AnimatedSprite(c);
                    for (int i = 1; i < 9; i++){
                        std::string filename = "Assets/Crystal/crystal" + std::to_string(i) + ".png";
                        as->AddImage(GetTexture(filename.c_str()));
                    }
                    c->SetSprite(as);
                    c->SetPosition(Vector2(x, y-16));
                }
                else if (a=='S'){
                    SpeedBoost* in = new SpeedBoost(this);
                    AnimatedSprite* as = new AnimatedSprite(in);
                    for (int i = 1; i < 7; i++){
                        std::string filename = "Assets/Red/frame " + std::to_string(i) + ".png";
                        as->AddImage(GetTexture(filename.c_str()));
                    }
                    in->SetSprite(as);
                    in->SetPosition(Vector2(x,y - 16));
                }
                else if (a == 'I'){
                    Invulnerability* in = new Invulnerability(this);
                    AnimatedSprite* as = new AnimatedSprite(in);
                    for (int i = 1; i < 7; i++){
                        std::string filename = "Assets/Blue/frame " + std::to_string(i) + ".png";
                        as->AddImage(GetTexture(filename.c_str()));
                    }
                    in->SetSprite(as);
                    in->SetPosition(Vector2(x,y - 16));
                }
                else if (a == 'G'){
                    MoonBounce* in = new MoonBounce(this);
                    AnimatedSprite* as = new AnimatedSprite(in);
                    for (int i = 1; i < 7; i++){
                        std::string filename = "Assets/Green/frame " + std::to_string(i) + ".png";
                        as->AddImage(GetTexture(filename.c_str()));
                    }
                    in->SetSprite(as);
                    in->SetPosition(Vector2(x,y - 16));
                }
                else if (a == 'X'){
                    DoubleCoin* in = new DoubleCoin(this);
                    AnimatedSprite* as = new AnimatedSprite(in);
                    for (int i = 1; i < 7; i++){
                        std::string filename = "Assets/Yellow/frame " + std::to_string(i) + ".png";
                        as->AddImage(GetTexture(filename.c_str()));
                    }
                    in->SetSprite(as);
                    in->SetPosition(Vector2(x,y - 16));
                }
                else{
                    Block* b = new Block(this);
                    b->SetTexture(a);
                    b->SetPosition(Vector2(x, y));
                }
            }
            x+=64;
        }
        x=32 + numLevels*56*64;
        y+=32;
    }
    levelIndex++;
    numLevels++;
}

void Game::UnloadData(){
    while (!actors.empty()){
        actors.pop_back();
    }
    for (std::unordered_map<std::string, SDL_Texture*>::iterator it = hashmap.begin();it!=hashmap.end();it++){
        SDL_DestroyTexture(it->second);
    }
    for (std::unordered_map<std::string, Mix_Chunk*>::iterator it = sounds.begin();it!=sounds.end();it++){
        Mix_FreeChunk(it->second);
    }
}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==0){
        window = SDL_CreateWindow("Lab06", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        IMG_Init(IMG_INIT_PNG);
        speed.x = 80;
        speed.y = 80;
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        LoadData();
		Mix_PlayChannel(1, GetSound("Assets/Music/LastParadise.wav"), -1);
        TTF_Init();

		mysql_init(&mysql);
		connection = mysql_real_connect(&mysql, mp_svrIP.c_str(), "root", "root", "CS201Proj", 0, 0, 0);
		if (connection == NULL)
			cout << mysql_error(&mysql) << endl;

		prevTime = SDL_GetTicks();
        return true;
    }
    return false;
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT){
            quit = false;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    for (int i=0; i<actors.size(); ++i){
        actors[i]->ProcessInput(state);
    }
    if (state[SDL_SCANCODE_ESCAPE]){
        quit = false;
    }
}

void Game::UpdateGame(){
    Uint32 currTime = SDL_GetTicks();
    while ((currTime-prevTime) < 16) {
        currTime = SDL_GetTicks();
    }
    float deltaTime = (float)(currTime - prevTime) / 1000.0f;
    if (deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    if (((PlayerMove*) mPlayer->GetMovement())->GetLives() == 0){
        mult = 0;
        Mix_Pause(1);
    }
    deltaTime *= mult;
    prevTime = currTime;
    if (score < 0){
        score = 0;
    }
    score += deltaTime * 100;
    std::vector<Actor*> temp = actors;
    for (Actor* a : temp){
        a->Update(deltaTime);
    }
    std::vector<Actor*> dead;
    for (Actor* a : actors){
        if (a->GetState()==a->EDead){
            dead.push_back(a);
        }
    }
    for (Actor* a : dead){
        delete a;
    }
}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    for (unsigned int i = 0; i < mSprites.size(); i++){
        mSprites[i]->Draw(renderer);
    }
    
    TTF_Font* font = TTF_OpenFont("ARCADECLASSIC.TTF", 24);
    SDL_Color White = {255, 255, 255};
    
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, std::to_string(score).c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
	SDL_Surface* sMessage = TTF_RenderText_Solid(font, std::to_string(GetOpponentScore()).c_str(), White);
	SDL_Texture* opponentScore = SDL_CreateTextureFromSurface(renderer, sMessage);

    SDL_Surface* lives = TTF_RenderText_Solid(font, ("x" + std::to_string(((PlayerMove*) mPlayer->GetMovement())->GetLives())).c_str(), White);
    SDL_Texture* livesMessage = SDL_CreateTextureFromSurface(renderer, lives);
    
    if (((PlayerMove*) mPlayer->GetMovement())->GetLives() == 0){
        SDL_Rect gameover_rect;
        gameover_rect.x = 0;
        gameover_rect.y = 0;
        gameover_rect.w = 1024;
        gameover_rect.h = 768;
        SDL_RenderCopy(renderer, GetTexture("Assets/gameover.png"), NULL, &gameover_rect);
        
        
        SDL_Rect Message_rect;
        int digits = 0;
        int temp = score;
        while (temp) {
            temp /= 10;
            digits++;
        }
        if (score == 0){
            digits = 1;
        }
        Message_rect.w = digits * 50;
        Message_rect.h = 100;
        Message_rect.x = 1024/2 - Message_rect.w/2;
        Message_rect.y = 530;
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		if (mp_isGuest == 0) {
			SDL_Rect opponentScore_rect;
			digits = 0;
			temp = GetOpponentScore();
			while (temp) {
				temp /= 10;
				digits++;
			}
			if (GetOpponentScore() == 0) {
				digits = 1;
			}
			opponentScore_rect.w = digits * 50;
			opponentScore_rect.h = 100;
			opponentScore_rect.x = 1024 / 2 - opponentScore_rect.w / 2;
			opponentScore_rect.y = 600;
			SDL_RenderCopy(renderer, opponentScore, NULL, &opponentScore_rect);
		}
		

    }
    
    else{
        SDL_Rect Message_rect;
        Message_rect.x = 20;
        Message_rect.y = 0;
        int digits = 0;
        int temp = score;
        while (temp) {
            temp /= 10;
            digits++;
        }
        if (score == 0){
            digits = 1;
        }
        Message_rect.w = digits * 25;
        Message_rect.h = 50;
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        
        SDL_Rect lives_rect;
        lives_rect.x = 1024-70;
        lives_rect.y = 0;
        lives_rect.w = 50;
        lives_rect.h = 50;
        SDL_RenderCopy(renderer, livesMessage, NULL, &lives_rect);
    
		if (mp_isGuest == 0) {
			SDL_Rect opponentScore_rect;
			opponentScore_rect.x = 500;
			opponentScore_rect.y = 0;
			digits = 0;
			temp = GetOpponentScore();
			while (temp) {
				temp /= 10;
				digits++;
			}
			if (GetOpponentScore() == 0) {
				digits = 1;
			}
			opponentScore_rect.w = digits * 25;
			opponentScore_rect.h = 50;
			SDL_RenderCopy(renderer, opponentScore, NULL, &opponentScore_rect);
		}

	}
    
    
    
    SDL_RenderPresent(renderer);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_FreeSurface(lives);
	SDL_FreeSurface(sMessage);
    TTF_CloseFont(font);
    SDL_DestroyTexture(Message);
    SDL_DestroyTexture(livesMessage);
	SDL_DestroyTexture(opponentScore);

}

MYSQL_ROW row;

MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query)
{
	if (mysql_query(connection, sql_query))
	{
		printf("MySQL query error : %s\n", mysql_error(connection));
		exit(1);
	}
	return mysql_use_result(connection);
}

//get the score from Databse where you need the gamename and whether your friend is playerA or playerB
int getScoreFromDatabase(MYSQL *connection, string gamename, int userID) {
	MYSQL_RES *result;
	string str = "SELECT points FROM Game WHERE userID = " + to_string(userID) + " AND gameName = '" + gamename + "' ;";
	int tmp = -1;
	result = mysql_perform_query(connection, (char *)str.c_str());
	while ((row = mysql_fetch_row(result)) != NULL) {
		//printf("%s %s\n", row[0], row[1]);
		tmp = stoi(row[0]);
	}
	mysql_free_result(result);
	return tmp;
}

//update your new score where you need the gamename and whether you are playerA or playerB
int updateScoreToDatabase(MYSQL *connection, string gamename, int newScore, int userID) {
	string str = "";
	str = "UPDATE Game SET points = " + to_string(newScore) + " WHERE userID = " + std::to_string(userID) + " AND gameName = '" + gamename + "' ;";
	MYSQL_RES *result;
	result = mysql_perform_query(connection, (char *)str.c_str());
	mysql_free_result(result);
	return 0;
}

int databaseconnect(Game* game)
{
	int a;
	int newOpponentScore = getScoreFromDatabase(game->connection, game->mp_gameName, game->mp_friendUserID);
	game->SetOpponentScore(newOpponentScore);
	std::cout << newOpponentScore << endl;
	cout << "Your score: " << getScoreFromDatabase(game->connection, game->mp_gameName, game->mp_yourUserID) << "Your friend's score: " << getScoreFromDatabase(game->connection, game->mp_gameName, game->mp_friendUserID) << endl;
	updateScoreToDatabase(game->connection, game->mp_gameName, (int)(game->GetScore()), game->mp_yourUserID);

	return 0;
}

void Game::RunLoop(){
	int waittime = 0;
	while (quit){
        ProcessInput();
        UpdateGame();
		waittime++;
		if (waittime >= 500 && mp_isGuest==0) {
			databaseconnect(this);
			waittime = 0;
		}
        GenerateOutput();
    }
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
	mysql_close(connection);
}
