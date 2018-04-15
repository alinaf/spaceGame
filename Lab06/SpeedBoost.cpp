//
//  SpeedBoost.cpp
//  Game-mac
//


#include <stdio.h>
#include "Game.h"
#include "SpeedBoost.h"
#include "PlayerMove.h"
#include "SDL/SDL_mixer.h"

SpeedBoost::SpeedBoost(class Game* game):Actor(game){
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}

void SpeedBoost::UpdateActor(float deltaTime){
    if (this->GetCollision()->Intersect(this->GetGame()->GetPlayer()->GetCollision())){
		((PlayerMove*) GetGame()->GetPlayer()->GetMovement())->SetSpeedMult(2.0f);
        this->SetState(Actor::EDead);
		Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/PowerUp.wav"), 0);
	}
    if (this->GetPosition().x - this->GetGame()->GetCameraPos().x < -this->GetCollision()->GetWidth()/2){
        this->SetState(Actor::EDead);

	}
}