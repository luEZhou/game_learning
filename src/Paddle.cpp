#include "Paddle.h"

#include "SDL3/SDL.h"

void Paddle::update(float dt)
{
	const bool* state = SDL_GetKeyboardState(nullptr);

	Vector2 velocity{0.0f, 0.0f};

	if (state[SDL_SCANCODE_A]) {
		velocity.setX(-1.0f);
	}
	if (state[SDL_SCANCODE_D]) {
		velocity.setX(1.0f);
	}

	if (velocity.lengthSquared() > 0.0f) {
		velocity.normalize();
	}

	position_ += velocity * speed_ * dt;

	if (position_.X() < 0.0f)
		position_.setX(0.0f);
	if (position_.X() > 1280.f - width_)
		position_.setX(1280.f - width_);
	if (position_.Y() < 0.0f)
		position_.setY(0.0f);
	if (position_.Y() > 720.f - height_ - 45)
		position_.setY(720.f - height_ - 45);
}
