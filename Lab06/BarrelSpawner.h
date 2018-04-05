//
//  BarrelSpawner.h
//  Game-mac
//
//  Created by tml on 2/21/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef BarrelSpawner_h
#define BarrelSpawner_h
#include "Actor.h"
#include "Barrel.h"
class BarrelSpawner: public Actor{
public:
    BarrelSpawner(Game* game);
    void UpdateActor(float deltaTime) override;
private:
    float timer;
};

#endif /* BarrelSpawner_h */
