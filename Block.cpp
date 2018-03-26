//
//  Block.cpp
//  Game-mac
//
//  Created by tml on 2/1/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Block.h"
#include "Game.h"

Block::Block(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(64, 32);
    this->GetGame()->GetBlocks()->push_back(this);
}

Block::~Block(){
    this->GetGame()->GetBlocks()->erase(std::find(this->GetGame()->GetBlocks()->begin(), this->GetGame()->GetBlocks()->end(), this));
}

void Block::SetTexture(char letter){
    if (letter == 'A'){
        mSprite->SetTexture(mGame->GetTexture("Assets/BlockA.png"));
    }
    else if (letter == 'B'){
        mSprite->SetTexture(mGame->GetTexture("Assets/BlockB.png"));
    }
    else if (letter == 'C'){
        mSprite->SetTexture(mGame->GetTexture("Assets/BlockC.png"));
    }
    else if (letter == 'D'){
        mSprite->SetTexture(mGame->GetTexture("Assets/BlockD.png"));
    }
    else if (letter == 'E'){
        mSprite->SetTexture(mGame->GetTexture("Assets/BlockE.png"));
    }
    else if (letter == 'F'){
        mSprite->SetTexture(mGame->GetTexture("Assets/BlockF.png"));
    }
}

void Block::UpdateActor(float deltaTime){
    if (this->GetPosition().x - this->GetGame()->GetCameraPos().x < -this->GetCollision()->GetWidth()/2){
        this->SetState(Actor::EDead);
    }
}
