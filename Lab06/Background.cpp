//
//  Background.cpp
//  Game-mac

#include <stdio.h>
#include "Background.h"
#include "Actor.h"
#include "Game.h"

Background::Background(class Actor* owner, int drawOrder):SpriteComponent(owner, drawOrder){
    drawCount = 0;
}

void Background::AddImage(SDL_Texture *image){
    mImages.push_back(image);
}

void Background::Draw(SDL_Renderer *renderer){
    drawCount = 0;
    for (unsigned int i = 0; i < mImages.size(); i++){
        if (i == 0){
            SDL_QueryTexture(mImages[i], nullptr, nullptr, &mTexWidth, &mTexHeight);
            SDL_Rect r;
            r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
            r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
            // Center the rectangle around the position of the owner
            r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + drawCount*mTexWidth - mOwner->GetGame()->GetCameraPos().x * mParallax);
            r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 - mOwner->GetGame()->GetCameraPos().y * mParallax);
            // Draw (have to convert angle from radians to degrees, and clockwise to counter)
            mTexture = mImages[i];
            SDL_RenderCopyEx(renderer,
                             mTexture,
                             nullptr,
                             &r,
                             -Math::ToDegrees(mOwner->GetRotation()),
                             nullptr,
                             SDL_FLIP_NONE);
            if (r.x >= 1024){
                break;
            }
            drawCount++;
        }
        else{
            SDL_QueryTexture(mImages[i-0], nullptr, nullptr, &mTexWidth, &mTexHeight);
            SDL_Rect r;
            r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
            r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
            // Center the rectangle around the position of the owner
            r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + drawCount*mTexWidth - mOwner->GetGame()->GetCameraPos().x * mParallax);
            r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 - mOwner->GetGame()->GetCameraPos().y * mParallax);
            // Draw (have to convert angle from radians to degrees, and clockwise to counter)
            mTexture = mImages[i];
            SDL_RenderCopyEx(renderer,
                             mTexture,
                             nullptr,
                             &r,
                             -Math::ToDegrees(mOwner->GetRotation()),
                             nullptr,
                             SDL_FLIP_NONE);
            if (r.x >= 1024){
                break;
            }
            drawCount++;
        }
        if (i == mImages.size()-1){
            i = -1;
        }
    }
}
