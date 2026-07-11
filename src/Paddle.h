#pragma once

#include "GameObject.h"
#include "Graphics/Texture2D.h"

class Paddle : public GameObject {

public:
	Paddle(
			Texture2D* texture,
			float x, float y, float width, float height, float speed) :
		GameObject(texture, x, y, width, height),
		speed_(speed)
	{
	}

	virtual ~Paddle() {}

	void update(float dt) override;

private:
	float speed_;
};