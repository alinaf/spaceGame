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
    rainbow = new AnimatedSprite(this);
    for (int i = 1; i < 11; i++){
        std::string filename = "Assets/Player/Rainbow" + std::to_string(i) + ".png";
        rainbow->AddImage(GetGame()->GetTexture(filename.c_str()));
    }
    run = new AnimatedSprite(this);
    for (int i = 1; i < 11; i++){
        std::string filename = "Assets/Player/Run" + std::to_string(i) + ".png";
        run->AddImage(GetGame()->GetTexture(filename.c_str()));
    }
}


void Player::UpdateActor(float deltaTime){
    if (mInvulnerable){
        invulnerableTimer += deltaTime;
        if (mSprite != rainbow){
            delete mSprite;
            mSprite = rainbow;
        }
    }
    if (invulnerableTimer > 3.0f){
        invulnerableTimer = 0.0f;
        mInvulnerable = false;
        if (mSprite != run){
            delete mSprite;
            mSprite = run;
        }
    }
}
