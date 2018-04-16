
//
//  Coin.cpp
//  Game-mac
//


#include <stdio.h>
#include "Coin.h"
#include "Game.h"

Coin::Coin(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}

void Coin::UpdateActor(float deltaTime){
    if (this->GetCollision()->Intersect(this->GetGame()->GetPlayer()->GetCollision())){
        Mix_PlayChannel(-1, this->GetGame()->GetSound("Assets/Crystal/Crystal.wav"), 0);
        this->GetGame()->AddScore(200);
        this->SetState(Actor::EDead);
    }
    if (this->GetPosition().x - this->GetGame()->GetCameraPos().x < -this->GetCollision()->GetWidth()/2){
        this->SetState(Actor::EDead);
    }
}
