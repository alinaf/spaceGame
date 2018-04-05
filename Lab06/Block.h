//
//  Block.h
//  Game-mac
//
//  Created by tml on 2/1/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef Block_h
#define Block_h
#include "Actor.h"

class Block: public Actor{
public:
    Block(class Game* game);
    ~Block();
    void SetTexture(char letter);
    void UpdateActor(float deltaTime) override;
};

#endif /* Block_h */
