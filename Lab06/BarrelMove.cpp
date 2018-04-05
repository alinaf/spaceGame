//
//  BarrelMove.cpp
//  Game-mac
//
//  Created by tml on 2/21/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "BarrelMove.h"
#include "Actor.h"
#include "Game.h"
#include "Player.h"

BarrelMove::BarrelMove(class Actor* owner):MoveComponent(owner){
    SetForwardSpeed(100.0f);
    SetAngularSpeed(-2*Math::Pi);
}

void BarrelMove::Update(float deltaTime){
    mOwner->SetPosition(Vector2(mOwner->GetPosition().x + deltaTime*GetForwardSpeed(), mOwner->GetPosition().y + deltaTime*mYSpeed));
    mOwner->SetRotation(mOwner->GetRotation() + GetAngularSpeed()*deltaTime);
    for (Block* a : *(mOwner->GetGame()->GetBlocks())){
        if (a->GetCollision()->Intersect(mOwner->GetCollision())){
            float dy1;
            dy1 = abs(a->GetCollision()->GetMin().y - mOwner->GetCollision()->GetMax().y);
            mOwner->SetPosition(Vector2(mOwner->GetPosition().x, mOwner->GetPosition().y-dy1));
            mYSpeed = 0.0f;
        }
    }
    if (mOwner->GetCollision()->Intersect(mOwner->GetGame()->GetPlayer()->GetCollision())){
        mOwner->GetGame()->GetPlayer()->SetPosition(mOwner->GetGame()->GetPlayerStart());
    }
    if (mOwner->GetPosition().y > 768.0f){
        mOwner->SetState(Actor::EDead);
    }
    mYSpeed += deltaTime*2000.0f;
}
