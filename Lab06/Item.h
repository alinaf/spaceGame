//
//  Item.h
//  Game-mac
//


#ifndef Item_h
#define Item_h
#include "Actor.h"

class Item: public Actor {
    
public:
    Item(class Game* game);
    void UpdateActor(float deltaTime) override;
private:
    float mTimer;
};

#endif /* Item_h */
