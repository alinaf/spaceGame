//
//  SpeedBoost.h
//  Game-mac
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
