//
//  Barrel.cpp
//  Game-mac


#include <stdio.h>
#include "Barrel.h"
#include "Game.h"

Barrel::Barrel(Game* game): Actor(game){
    mSprite = new SpriteComponent(this, 150);
    mMovement = new BarrelMove(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}
