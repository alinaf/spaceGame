#pragma once
#include "Component.h"
#include "SDL/SDL.h"
class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	// Draw this sprite
	virtual void Draw(SDL_Renderer* renderer);
	// Set the texture to draw for this psirte
	virtual void SetTexture(SDL_Texture* texture);

	// Get the draw order for this sprite
	int GetDrawOrder() const { return mDrawOrder; }
	// Get the width/height of the texture
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	// Texture to draw
	SDL_Texture* mTexture;
	// Draw order
	int mDrawOrder;
	// Width/height
	int mTexWidth;
	int mTexHeight;
};
