//
//  Player.h
//  Game-mac
//


#ifndef Player_h
#define Player_h
#include "Actor.h"
#include "PlayerMove.h"
#include "AnimatedSprite.h"
#include <string>

class Player: public Actor {
public:
    Player(Game* game);
    void UpdateActor(float deltaTime) override;
    void SetInvulnerable(bool b) {mInvulnerable = b;}
    bool GetInvulnerable() {return mInvulnerable;}
private:
    bool mInvulnerable = false;
    float invulnerableTimer = 0.0f;
    std::string currSprite = "run";
//    AnimatedSprite* rainbow;
//    AnimatedSprite* run;
};

#endif /* Player_h */
