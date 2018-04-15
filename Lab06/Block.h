//
//  Block.h
//  Game-mac
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
