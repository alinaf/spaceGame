//
//  SpeedBoost.h
//  Game-mac
//
//  Created by tml on 4/14/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef SpeedBoost_h
#define SpeedBoost_h
#include "Actor.h"

class SpeedBoost: public Actor {
    
public:
    SpeedBoost(class Game* game);
    void UpdateActor(float deltaTime) override;
};

#endif /* SpeedBoost_h */
