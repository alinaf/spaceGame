//
//  BarrelSpawner.cpp
//  Game-mac

#include <stdio.h>
#include "BarrelSpawner.h"
#include "Game.h"
#include <ranlib.h>

BarrelSpawner::BarrelSpawner(Game* game): Actor(game){
    timer = 3.0f;
}

void BarrelSpawner::UpdateActor(float deltaTime){
    timer-=deltaTime;
    if (timer <= 0){
        if (rand() % 1000 == 0){
            Barrel* b = new Barrel(this->GetGame());
            b->GetSprite()->SetTexture(this->GetGame()->GetTexture("Assets/Barrel.png"));
            b->SetPosition(Vector2(this->GetPosition().x, this->GetPosition().y));
            timer = 3.0f;
        }
        
    }
    if (mPosition.x - GetGame()->GetCameraPos().x < 0){
        this->SetState(Actor::EDead);
    }
}
