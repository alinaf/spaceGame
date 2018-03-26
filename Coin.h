//
//  Coin.h
//  Game-mac
//
//  Created by tml on 2/25/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef Coin_h
#define Coin_h
#include "Actor.h"

class Coin: public Actor{
public:
    Coin(class Game* game);
    void UpdateActor(float deltaTime) override;
};

#endif /* Coin_h */
