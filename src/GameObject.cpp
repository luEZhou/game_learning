#include "GameObject.h"

#include "SDL3/SDL.h"

void GameObject::render(SDL_Renderer* renderer)
{
	if (!texture_ || !texture_->isLoaded()) {
		return;
	}

	SDL_FRect dst{
			position_.X(),
			position_.Y(),
			width_,
			height_};
	texture_->draw(renderer, dst);
}