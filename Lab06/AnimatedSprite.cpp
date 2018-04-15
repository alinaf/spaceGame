//
//  AnimatedSprite.cpp
//  Game-mac


#include <stdio.h>
#include "AnimatedSprite.h"
#include "Actor.h"
#include "Game.h"
#include <string>

AnimatedSprite::AnimatedSprite(class Actor* owner, int drawOrder):SpriteComponent(owner, drawOrder){
    mAnimTimer = 0.0f;
    mAnimSpeed = 15.0f;
}

void AnimatedSprite::AddImage(SDL_Texture *image){
    mImages.push_back(image);
}

void AnimatedSprite::Update(float deltaTime){
    SpriteComponent::Update(deltaTime);
    size_t frameCount = mImages.size();
    if (frameCount > 0)
    {
        mAnimTimer += mAnimSpeed * deltaTime;
        while (mAnimTimer >= frameCount)
            mAnimTimer -= frameCount;
        while (mAnimTimer < 0.0f)
            mAnimTimer += frameCount;
        SetTexture(mImages[(int)mAnimTimer]);
    }
    
}
