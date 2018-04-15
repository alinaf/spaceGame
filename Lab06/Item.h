//
//  Item.h
//  Game-mac
//
//  Created by tml on 4/5/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
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
