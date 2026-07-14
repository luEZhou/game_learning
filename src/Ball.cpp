#include "Ball.h"

Ball::Ball(
		Texture2D* texture,
		float x,
		float y,
		float width,
		float height,
		float speed) :
	GameObject(texture, x, y, width, height),
	speed_(speed)
{
	velocity_.setX(0.0f);
	velocity_.setY(-1.0f);
	velocity_.normalize();
}

void Ball::update(float dt)
{
	position_ += velocity_ * speed_ * dt;

	if (position_.X() < 0.0f) {
		position_.setX(0.0f);
		velocity_.setX(-velocity_.X());
	}
	if (position_.X() > 1280.f - width_) {
		position_.setX(1280.f - width_);
		velocity_.setX(-velocity_.X());
	}
	if (position_.Y() < 0.0f) {
		position_.setY(0.0f);
		velocity_.setY(-velocity_.Y());
	}

	if (position_.Y() >= 720.0f - 20.f - 45.f - height_) {
		position_.setY(720.0f - 20.f - 45.f - height_);
		velocity_.setY(-velocity_.Y());
	}
}

void Ball::reset(float x, float y)
{
	position_.setX(x);
	position_.setY(y);

	velocity_.setX(1.0f);
	velocity_.setY(-1.0f);
	velocity_.normalize();
}

void Ball::setDirection(float x, float y)
{
	velocity_.setX(x);
	velocity_.setY(y);

	if (velocity_.lengthSquared() > 0.0f) {
		velocity_.normalize();
	}
}