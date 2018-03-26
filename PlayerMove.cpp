//
//  PlayerMove.cpp
//  Game-mac
//
//  Created by tml on 2/8/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "PlayerMove.h"
#include "Actor.h"
#include "Game.h"

PlayerMove::PlayerMove(class Actor* owner):MoveComponent(owner){
    mSpacePressed = false;
    mInAir = false;
    this->SetForwardSpeed(300.0f);
}

void PlayerMove::ProcessInput(const Uint8* keyState){
//    if (keyState[SDL_SCANCODE_LEFT]){
//        this->SetForwardSpeed(-300.0f);
//    }
//    else if (keyState[SDL_SCANCODE_RIGHT]){
//        this->SetForwardSpeed(300.0f);
//    }
//    else{
//        this->SetForwardSpeed(0);
//    }
    if (mSpacePressed == false && keyState[SDL_SCANCODE_SPACE] == true){
        if (!mInAir){
            mInAir = true;
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Player/Jump.wav"), 0);
            mYSpeed = -500.0f;
            firstJump = SDL_GetTicks()/1000.0f;
        }
    }
    mSpacePressed = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::Update(float deltaTime){
    mOwner->SetPosition(Vector2(mOwner->GetPosition().x + deltaTime*this->GetForwardSpeed(), mOwner->GetPosition().y + deltaTime*mYSpeed));
    for (Block* a : *(mOwner->GetGame()->GetBlocks())){
        if (a->GetCollision()->Intersect(mOwner->GetCollision())){
            float dx1, dx2, dy1, dy2;
            float min = 0;
            std::vector<Block*> b = *(mOwner->GetGame()->GetBlocks());
            dy2 = abs(a->GetCollision()->GetMax().y - mOwner->GetCollision()->GetMin().y);
            dy1 = abs(a->GetCollision()->GetMin().y - mOwner->GetCollision()->GetMax().y);
            dx1 = abs(a->GetCollision()->GetMin().x - mOwner->GetCollision()->GetMax().x);
            dx2 = abs(a->GetCollision()->GetMax().x - mOwner->GetCollision()->GetMin().x);
            min = Math::Min(dy1, Math::Min(dy2, Math::Min(dx1, dx2)));
            if (min == dy1){
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x, mOwner->GetPosition().y-dy1));
                mYSpeed = 0.0f;
                mInAir = false;
            }
            if (min == dy2){
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x, mOwner->GetPosition().y+dy2));
                mYSpeed = 0.0f;
            }
            if (min == dx1){
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x - dx1, mOwner->GetPosition().y));
            }
            if (min == dx2){
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x + dx2, mOwner->GetPosition().y));
            }
        }
    }
    
    if (mOwner->GetPosition().y > 768.0f){
        mOwner->SetPosition(Vector2(mOwner->GetPosition().x, 768.0f));
        mInAir = false;
    }
    
    mOwner->GetGame()->SetCameraPos(Vector2(mOwner->GetPosition().x - 512, 0));
    if (mSpacePressed){
        if (SDL_GetTicks()/1000.0f - firstJump <= 0.3){
            mYSpeed -= deltaTime*1500.0f;
        }
    }
    if(mOwner->GetGame()->GetCameraPos().x >= 2560 * mOwner->GetGame()->numLevels){
        mOwner->GetGame()->LoadNextLevel();
    }
    mYSpeed += deltaTime*2000.0f;
}
