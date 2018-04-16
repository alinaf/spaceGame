//
//  Game.cpp
//  Game-mac
//


#include "Game.h"
#include "Actor.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <fstream>
#include <iostream>
#include <string>
//#include "mysql.h"
//#pragma comment(lib, "libmysql")
//#pragma comment(lib, "mysqlclient")
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
		Mix_VolumeChunk(sound, 10);
	}
	else if (filename == "Assets/Crystal/Crystal.wav") {
		Mix_VolumeChunk(sound, 30);
	}
    else if (filename == "Assets/Sounds/Gravity.wav") {
        Mix_VolumeChunk(sound, 20);
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
    
	LoadSound("Assets/Music/LastParadise.wav");
	LoadSound("Assets/Sounds/PowerUp.wav");
	LoadSound("Assets/Sounds/PowerDown.wav");
    LoadSound("Assets/Sounds/Gravity.wav");
	LoadSound("Assets/Player/Falling.wav");
	LoadSound("Assets/Player/Scream.wav");
	LoadSound("Assets/Player/Jump.wav");
	LoadSound("Assets/Crystal/Crystal.wav");


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
		Mix_PlayChannel(1, GetSound("Assets/Music/LastParadise.wav"), 0);
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
    prevTime = currTime;
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
    SDL_RenderPresent(renderer);
}

//MYSQL *connection, mysql;
//MYSQL_ROW row;
//
//MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query)
//{
//    if (mysql_query(connection, sql_query))
//    {
//        printf("MySQL query error : %s\n", mysql_error(connection));
//        exit(1);
//    }
//    return mysql_use_result(connection);
//}
//
////get the score from Databse where you need the gamename and whether your friend is playerA or playerB
//int getScoreFromDatabase(string gamename, bool isHost) {
//    MYSQL_RES *result;
//    string str = "SELECT pointA, pointB FROM Game WHERE gameName = '" + gamename + "' ;";
//    int tmp = -1;
//    result = mysql_perform_query(connection, (char *)str.c_str());
//    while ((row = mysql_fetch_row(result)) != NULL) {
//        //printf("%s %s\n", row[0], row[1]);
//        if (isHost)
//            tmp = stoi(row[0]);
//        else
//            tmp = stoi(row[1]);
//    }
//    mysql_free_result(result);
//    return tmp;
//}
//
////update your new score where you need the gamename and whether you are playerA or playerB
//int updateScoreToDatabase(string gamename, int newScore, bool isHost) {
//    string str = "";
//    if (isHost)
//        str = "UPDATE Game SET pointA = " + to_string(newScore) + " WHERE gameName = '" + gamename + "' ;";
//    else
//        str = "UPDATE Game SET pointB = " + to_string(newScore) + " WHERE gameName = '" + gamename + "' ;";
//    MYSQL_RES *result;
//    result = mysql_perform_query(connection, (char *)str.c_str());
//    mysql_free_result(result);
//    return 0;
//}
//
////nothing .. for test
//int displayGameTable(string gamename) {
//    MYSQL_RES *result;
//    string str = "SELECT U1.userName, pointA, U2.userName, pointB FROM Game, Users U1, Users U2 WHERE Game.gameName = '" + gamename + "' AND U1.userID=Game.userAID AND U2.userID=Game.userBID;";
//    result = mysql_perform_query(connection, (char *)str.c_str());
//    printf("MySQL Tables in mysql database:\n");
//    while ((row = mysql_fetch_row(result)) != NULL)
//        printf("%s %s %s %s\n", row[0], row[1], row[2], row[3]);
//    mysql_free_result(result);
//    return 0;
//}
//
//int databaseconnect()
//{
//    int a;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql, "localhost", "root", "root", "CS201Proj", 0, 0, 0);
//    if (connection == NULL)
//        cout << mysql_error(&mysql) << endl;
//
//    //displayGameTable("Test111");
//    cout << "Your score: " << getScoreFromDatabase("Test111", true) << "    Your friend's score: " << getScoreFromDatabase("Test111", false) << endl;
//    updateScoreToDatabase("Test111", (int) (rand() * 10), true);
//    /*updateScoreToDatabase("Test111", 77, true);
//    displayGameTable("Test111");
//    cin >> a;*/
//
//    mysql_close(connection);
//    return 0;
//}

void Game::RunLoop(){
	int waittime = 0;
	while (quit){
        ProcessInput();
        UpdateGame();
		waittime++;
		if (waittime >= 500) {
			//databaseconnect();
			waittime = 0;
		}
        GenerateOutput();
    }
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
}
