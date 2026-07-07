#include "Player.h"

#include "SDL3/SDL.h"

void Player::update(float dt)
{
	const bool* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_W]) {
		y_ -= speed_ * dt;
	}
	if (state[SDL_SCANCODE_S]) {
		y_ += speed_ * dt;
	}
	if (state[SDL_SCANCODE_A]) {
		x_ -= speed_ * dt;
	}
	if (state[SDL_SCANCODE_D]) {
		x_ += speed_ * dt;
	}

	if (x_ < 0.0f)
		x_ = 0.0f;
	if (x_ > 1280.0f - width_)
		x_ = 1280.0f - width_;
	if (y_ < 0.0f)
		y_ = 0.0f;
	if (y_ > 720.0f - height_)
		y_ = 720.0f - height_;
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_FRect playerRect = {x_, y_, width_, height_};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &playerRect);
}
