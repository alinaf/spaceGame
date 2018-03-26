#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mGame->AddActor(this);
    mSprite = nullptr;
    mMovement = nullptr;
    mCollision = nullptr;
}

Actor::~Actor()
{
	// TODO
    mGame->RemoveActor(this);
    delete mSprite;
    delete mMovement;
    delete mCollision;
}

Vector2 Actor::GetForward() const{
    float angle = this->GetRotation();
    float y = -Math::Sin(angle);
    float x = Math::Cos(angle);
    return Vector2(x, y);
}

void Actor::Update(float deltaTime)
{
	// TODO
    if (mState == EActive){
        //update components
        if (mMovement != nullptr){
            mMovement->Update(deltaTime);
        }
        if (mSprite != nullptr){
            mSprite->Update(deltaTime);
        }
        if (mCollision != nullptr){
            mCollision->Update(deltaTime);
        }
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// TODO
    if (mState == EActive){
        //ProcessInput on all components
        if (mMovement != nullptr){
            mMovement->ProcessInput(keyState);
        }
        if (mSprite != nullptr){
            mSprite->ProcessInput(keyState);
        }
        if (mCollision != nullptr){
            mCollision->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const Uint8* keyState)
{
}
