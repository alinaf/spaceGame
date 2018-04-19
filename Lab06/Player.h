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
    void SetInvulnerable(bool b) {mInvulnerable = b; if (mInvulnerable) invulnerableTimer = 0;}
    bool GetInvulnerable() {return mInvulnerable;}
    void SetDoubleCoin(bool b) {doubleCoin = b; if (doubleCoin) doubleCoinTimer = 0;}
    bool GetDoubleCoin() {return doubleCoin;}
private:
    bool mInvulnerable = false;
    float invulnerableTimer = 0.0f;
    std::string currSprite = "run";
    bool doubleCoin = false;
    float doubleCoinTimer = 0.0f;
//    AnimatedSprite* rainbow;
//    AnimatedSprite* run;
};

#endif /* Player_h */
