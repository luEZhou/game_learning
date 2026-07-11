#include "Brick.h"

void Brick::render(SDL_Renderer* renderer)
{
	if (!alive_) {
		return;
	}

	GameObject::render(renderer);
}