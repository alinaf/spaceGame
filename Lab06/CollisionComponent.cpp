#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	// TODO: Implement
    if (!(this->GetMax().x < other->GetMin().x) && !(other->GetMax().x < this->GetMin().x) && !(this->GetMax().y < other->GetMin().y) && !(other->GetMax().y < this->GetMin().y)){
        return true;
    }
	return false;
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
    if (mOwner){
        Vector2 min;
        min.x = mOwner->GetPosition().x - (GetWidth()*mOwner->GetScale())/2.0f;
        min.y = mOwner->GetPosition().y - (GetHeight()*mOwner->GetScale())/2.0f;
        return min;
    }
    return Vector2::Zero;
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
    if (mOwner){
        Vector2 max;
        max.x = mOwner->GetPosition().x + (GetWidth()*mOwner->GetScale())/2.0f;
        max.y = mOwner->GetPosition().y + (GetHeight()*mOwner->GetScale())/2.0f;
        return max;
    }
    return Vector2::Zero;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

