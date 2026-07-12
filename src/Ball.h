#pragma once

#include "GameObject.h"

class Texture2D;

class Ball : public GameObject {

public:
	Ball(
			Texture2D* texture,
			float x,
			float y,
			float width,
			float height,
			float speed);

	virtual ~Ball() = default;

	void update(float dt) override;

	void reset(float x, float y);

	void setDirection(float x, float y);

	const Vector2& getVelocity() const { return velocity_; }

	void setVelocity(const Vector2& velocity)
	{
		velocity_ = velocity;
	}

protected:
	Vector2 velocity_;
	float speed_;
};