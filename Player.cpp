//
//  Player.cpp
//  Game-mac
//
//  Created by tml on 2/8/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Player.h"
#include "Game.h"

Player::Player(Game* game): Actor(game){
    mSprite = new SpriteComponent(this, 200);
    mMovement = new PlayerMove(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(20, 64);
}
