//
//  BarrelMove.cpp
//  Game-mac


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
    mOwner->SetPosition(Vector2(mOwner->GetPosition().x + deltaTime * GetForwardSpeed(), mOwner->GetPosition().y + deltaTime*500.0f));
    mOwner->SetRotation(mOwner->GetRotation() + GetAngularSpeed()*deltaTime);
    for (Block* a : mOwner->GetGame()->GetBlocks()){
        if (a->GetCollision()->Intersect(mOwner->GetCollision())){
            mOwner->SetState(Actor::EDead);
            a->SetState(Actor::EDead);
        }
    }
    if (mOwner->GetCollision()->Intersect(mOwner->GetGame()->GetPlayer()->GetCollision())){
<<<<<<< HEAD
        if (!mOwner->GetGame()->GetPlayer()->GetInvulnerable()){
            mOwner->GetGame()->GetPlayer()->SetPosition(Vector2(mOwner->GetGame()->GetPlayer()->GetPosition().x, 768-32-32));
        }
=======
        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Player/Scream.wav"), 0);
		mOwner->GetGame()->GetPlayer()->SetPosition(Vector2(mOwner->GetGame()->GetPlayer()->GetPosition().x, 768-32-32));
>>>>>>> 8dd62f0cbe347a6f99a7146840c6a0cb9646f3e3
    }
    if (mOwner->GetPosition().y > 768.0f){
        mOwner->SetState(Actor::EDead);
    }
    if (mOwner->GetPosition().x - mOwner->GetGame()->GetCameraPos().x < 0){
        mOwner->SetState(Actor::EDead);
    }
}
