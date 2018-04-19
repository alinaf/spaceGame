//
//  DoubleCoin.cpp
//  Game-mac
//
//  Created by tml on 4/18/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Game.h"
#include "DoubleCoin.h"
#include "Coin.h"
#include "Player.h"

DoubleCoin::DoubleCoin(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}

void DoubleCoin::UpdateActor(float deltaTime){
    if (this->GetCollision()->Intersect(this->GetGame()->GetPlayer()->GetCollision())){
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/Coin_up.wav"), 0);
        GetGame()->GetPlayer()->SetDoubleCoin(true);
        this->SetState(Actor::EDead);
    }
    if (this->GetPosition().x - this->GetGame()->GetCameraPos().x < -this->GetCollision()->GetWidth()/2){
        this->SetState(Actor::EDead);
        
    }
}
