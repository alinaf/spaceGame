//
//  MoonBounce.h
//  Game-mac
//
//  Created by tml on 4/15/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef MoonBounce_h
#define MoonBounce_h
#include "Actor.h"

class MoonBounce: public Actor {
    
public:
    MoonBounce(class Game* game);
    void UpdateActor(float deltaTime) override;
};

#endif /* MoonBounce_h */
