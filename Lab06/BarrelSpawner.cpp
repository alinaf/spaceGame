//
//  BarrelSpawner.cpp
//  Game-mac

#include <stdio.h>
#include "BarrelSpawner.h"
#include "Game.h"
#ifndef _WIN32
#include <ranlib.h>
#endif

BarrelSpawner::BarrelSpawner(Game* game): Actor(game){
    timer = 3.0f;
}

void BarrelSpawner::UpdateActor(float deltaTime){
    timer-=deltaTime;
    if (timer <= 0){
        if (rand() % 800 == 0){
            Barrel* b = new Barrel(this->GetGame());
            AnimatedSprite* as = new AnimatedSprite(b);
            for (int i = 1; i < 12; i++){
                std::string filename = "Assets/glitch_meteor/meteor000" + std::to_string(i) + ".png";
                as->AddImage(GetGame()->GetTexture(filename.c_str()));
            }
            b->SetSprite(as);
            b->SetPosition(Vector2(this->GetPosition().x, this->GetPosition().y));
            timer = 3.0f;
        }
        
    }
    if (mPosition.x - GetGame()->GetCameraPos().x < 0){
        this->SetState(Actor::EDead);
    }
}
