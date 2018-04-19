//
//  PlayerMove.h
//  Game-mac
//


#ifndef PlayerMove_h
#define PlayerMove_h
#include "MoveComponent.h"

class PlayerMove: public MoveComponent{
public:
    enum MoveState{
        OnGround,
        Jump,
        Falling
    };
    enum CollSide{
        None, Top, Bottom, Right, Left
    };
    PlayerMove (class Actor* owner);
    void ProcessInput(const Uint8* keyState) override;
    void Update(float deltaTime) override;
    void SetSpeedMult(float num) {mSpeedMult = num;}
    void SetGravity(float g) {mGravity = g;}
    int GetLives() {return mLives;}
    void DecreaseLives() {mLives--; if (mLives < 0) mLives = 0;}
private:
    float mYSpeed = 0.0f;
    bool mSpacePressed;
    bool mInAir;
    float firstJump;
    float mXSpeed = 400.0f;
    bool mAccelerate = false;
    float mSpeedMult = 1.0f;
    float mSpeedBoostTimer = 0.0f;
    float mGravity = 2000.0f;
    float mMoonBounceTimer = 0.0f;
    int mLives = 3;
};

#endif /* PlayerMove_h */
