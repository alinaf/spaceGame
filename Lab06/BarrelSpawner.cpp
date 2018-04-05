//
//  BarrelSpawner.cpp
//  Game-mac
//
//  Created by tml on 2/21/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "BarrelSpawner.h"
#include "Game.h"

BarrelSpawner::BarrelSpawner(Game* game): Actor(game){
    timer = 3.0f;
}

void BarrelSpawner::UpdateActor(float deltaTime){
    timer-=deltaTime;
    if (timer <= 0){
        Barrel* b = new Barrel(this->GetGame());
        b->GetSprite()->SetTexture(this->GetGame()->GetTexture("Assets/Barrel.png"));
        b->SetPosition(Vector2(this->GetPosition().x, this->GetPosition().y));
        timer = 3.0f;
    }
}
