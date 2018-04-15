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
#include <ranlib.h>

BarrelMove::BarrelMove(class Actor* owner):MoveComponent(owner){
    SetForwardSpeed(-200.0f - (rand()%10) * 50.0f);
    SetAngularSpeed(-2*Math::Pi);
}

void BarrelMove::Update(float deltaTime){
    mOwner->SetPosition(Vector2(mOwner->GetPosition().x + deltaTime*GetForwardSpeed(), mOwner->GetPosition().y + deltaTime*500.0f));
    mOwner->SetRotation(mOwner->GetRotation() + GetAngularSpeed()*deltaTime);
    for (Block* a : *(mOwner->GetGame()->GetBlocks())){
        if (a->GetCollision()->Intersect(mOwner->GetCollision())){
            mOwner->SetState(Actor::EDead);
            a->SetState(Actor::EDead);
        }
    }
    if (mOwner->GetCollision()->Intersect(mOwner->GetGame()->GetPlayer()->GetCollision())){
        mOwner->GetGame()->GetPlayer()->SetPosition(Vector2(mOwner->GetGame()->GetPlayer()->GetPosition().x, 768-32-32));
    }
    if (mOwner->GetPosition().y > 768.0f){
        mOwner->SetState(Actor::EDead);
    }
    mYSpeed += deltaTime*2000.0f;
}
