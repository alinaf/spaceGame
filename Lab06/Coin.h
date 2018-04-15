//
//  Coin.h
//  Game-mac
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
