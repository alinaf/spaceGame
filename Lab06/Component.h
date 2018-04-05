#pragma once
#include <SDL/SDL_stdinc.h>

class Component
{
public:
	// Constructor
	Component(class Actor* owner);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	// Process input for this component (if needed)
	virtual void ProcessInput(const Uint8* keyState);
protected:
	// Owning actor
	class Actor* mOwner;
};
