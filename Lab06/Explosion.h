//
//  Explosion.h
//  Game-mac
//
//  Created by tml on 4/17/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef Explosion_h
#define Explosion_h
#include "Actor.h"

class Explosion: public Actor {
public:
    Explosion(class Game* game);
    void UpdateActor(float deltaTime) override;
private:
    float mTimer;
};

#endif /* Explosion_h */
