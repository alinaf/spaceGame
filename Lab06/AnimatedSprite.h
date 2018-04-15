//
//  AnimatedSprite.h
//  Game-mac


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
