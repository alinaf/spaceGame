//
//  BarrelMove.cpp
//  Game-mac


#include <stdio.h>
#include "BarrelMove.h"
#include "Actor.h"
#include "Game.h"
#include "Player.h"
#ifndef _WIN32
#include <ranlib.h>
#endif
#include "Explosion.h"
#include "PlayerMove.h"

BarrelMove::BarrelMove(class Actor* owner):MoveComponent(owner){
    SetForwardSpeed(-100.0f - (rand()%10) * 25.0f);
//    SetAngularSpeed(-2*Math::Pi);
}

void BarrelMove::Update(float deltaTime){
    mOwner->SetPosition(Vector2(mOwner->GetPosition().x + deltaTime * GetForwardSpeed(), mOwner->GetPosition().y + deltaTime*300.0f));
    mOwner->SetRotation(Math::Atan2(GetForwardSpeed(), 300.0f));
    for (Block* a : mOwner->GetGame()->GetBlocks()){
        if (a->GetCollision()->Intersect(mOwner->GetCollision())){
            Explosion* ex = new Explosion(mOwner->GetGame());
            AnimatedSprite* as = new AnimatedSprite(ex);
            for (int i = 1; i < 11; i++){
                std::string filename = "Assets/Bubble_Explo/bubble_explo" + std::to_string(i) + ".png";
                as->AddImage(mOwner->GetGame()->GetTexture(filename.c_str()));
            }
            ex->SetSprite(as);
            ex->SetPosition(mOwner->GetPosition());
            ex->SetScale(1.5f);
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/explosion.wav"), 0);
            mOwner->SetState(Actor::EDead);
            a->SetState(Actor::EDead);
        }
    }
    if (mOwner->GetCollision()->Intersect(mOwner->GetGame()->GetPlayer()->GetCollision())){
        if (!mOwner->GetGame()->GetPlayer()->GetInvulnerable()){
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Player/Scream.wav"), 0);
            mOwner->GetGame()->AddScore(-1000);
            ((PlayerMove*)mOwner->GetGame()->GetPlayer()->GetMovement())->DecreaseLives();
            mOwner->GetGame()->GetPlayer()->SetInvulnerable(true);
            mOwner->GetGame()->GetPlayer()->SetPosition(Vector2(mOwner->GetGame()->GetPlayer()->GetPosition().x, 0.0f));
        }

    }
    if (mOwner->GetPosition().y > 768.0f){
        mOwner->SetState(Actor::EDead);
    }
    if (mOwner->GetPosition().x - mOwner->GetGame()->GetCameraPos().x < 0){
        mOwner->SetState(Actor::EDead);
    }
}
