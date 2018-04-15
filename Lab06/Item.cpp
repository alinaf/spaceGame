//
//  Item.cpp
//  Game-mac
//


#include <stdio.h>
#include "Game.h"
#include "Item.h"

Item::Item(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}

void Item::UpdateActor(float deltaTime){
    if (this->GetCollision()->Intersect(this->GetGame()->GetPlayer()->GetCollision())){
        GetGame()->GetPlayer()->GetMovement()->SetForwardSpeed(600.0f);
        this->SetState(Actor::EDead);
    }
    if (this->GetPosition().x - this->GetGame()->GetCameraPos().x < -this->GetCollision()->GetWidth()/2){
        this->SetState(Actor::EDead);
    }
}
