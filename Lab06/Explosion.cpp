//
//  Explosion.cpp
//  Game-mac
//
//  Created by tml on 4/17/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Game.h"
#include "Explosion.h"

Explosion::Explosion(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
}

void Explosion::UpdateActor(float deltaTime){
    mTimer += deltaTime;
    if (mTimer > 0.5f){
        SetState(EDead);
    }
}
