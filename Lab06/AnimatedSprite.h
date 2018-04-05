//
//  AnimatedSprite.h
//  Game-mac
//
//  Created by tml on 2/25/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef AnimatedSprite_h
#define AnimatedSprite_h
#include "SpriteComponent.h"
#include <vector>

class AnimatedSprite: public SpriteComponent{
public:
    AnimatedSprite(class Actor* owner, int drawOrder = 100);
    void AddImage(SDL_Texture* image);
    void Update(float deltaTime) override;
private:
    std::vector<SDL_Texture*> mImages;
    float mAnimTimer;
    float mAnimSpeed;
};

#endif /* AnimatedSprite_h */
