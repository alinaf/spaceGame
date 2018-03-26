//
//  Background.h
//  Game-mac
//
//  Created by tml on 2/22/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#ifndef Background_h
#define Background_h
#include "SpriteComponent.h"
#include <vector>

class Background: public SpriteComponent{
public:
    Background(class Actor* owner, int drawOrder = 100);
    void AddImage(SDL_Texture* image);
    void Draw(SDL_Renderer* renderer) override;
    float mParallax = 1.0f;
private:
    std::vector<SDL_Texture*> mImages;
    int drawCount;
};

#endif /* Background_h */
