//
//  Barrel.cpp
//  Game-mac
//
//  Created by tml on 2/21/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Barrel.h"
#include "Game.h"

Barrel::Barrel(Game* game): Actor(game){
    mSprite = new SpriteComponent(this, 150);
    mMovement = new BarrelMove(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}
