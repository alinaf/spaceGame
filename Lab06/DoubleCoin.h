//
//  DoubleCoin.h
//  Game-mac
//
//  Created by tml on 4/18/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef DoubleCoin_h
#define DoubleCoin_h
#include "Actor.h"

class DoubleCoin: public Actor {
public:
    DoubleCoin(class Game* game);
    void UpdateActor(float deltaTime) override;
};

#endif /* DoubleCoin_h */
