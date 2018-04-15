//
//  BarrelMove.h
//  Game-mac

#ifndef BarrelMove_h
#define BarrelMove_h
#include "MoveComponent.h"

class BarrelMove: public MoveComponent{
public:
    BarrelMove (class Actor* owner);
    void Update(float deltaTime) override;
private:
    float mYSpeed = 0.0f;
};

#endif /* BarrelMove_h */
