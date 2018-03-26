//
//  PlayerMove.h
//  Game-mac
//
//  Created by tml on 2/8/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef PlayerMove_h
#define PlayerMove_h
#include "MoveComponent.h"

class PlayerMove: public MoveComponent{
public:
    PlayerMove (class Actor* owner);
    void ProcessInput(const Uint8* keyState) override;
    void Update(float deltaTime) override;
private:
    float mYSpeed = 0.0f;
    bool mSpacePressed;
    bool mInAir;
    float firstJump;
};

#endif /* PlayerMove_h */
