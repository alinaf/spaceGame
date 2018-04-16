//
//  MoonBounce.cpp
//  Game-mac
//
//  Created by tml on 4/15/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "MoonBounce.h"
#include "Game.h"
#include "PlayerMove.h"
#include "SDL/SDL_mixer.h"

MoonBounce::MoonBounce(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}

void MoonBounce::UpdateActor(float deltaTime){
    if (this->GetCollision()->Intersect(this->GetGame()->GetPlayer()->GetCollision())){
        ((PlayerMove*) this->GetGame()->GetPlayer()->GetMovement())->SetGravity(1000.0f);
        this->SetState(Actor::EDead);
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/Gravity.wav"), 0);
    }
    if (this->GetPosition().x - this->GetGame()->GetCameraPos().x < -this->GetCollision()->GetWidth()/2){
        this->SetState(Actor::EDead);
    }
}
