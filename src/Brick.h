#pragma once

#include "GameObject.h"

class Brick : public GameObject {

public:
	Brick(
			Texture2D* texture,
			float x,
			float y,
			float width,
			float height) :
		GameObject(texture, x, y, width, height)
	{
	}

	virtual ~Brick() = default;

	bool isAlive() const { return alive_; }

	void destroy() { alive_ = false; }

	void update(float dt) override {}

	void render(SDL_Renderer* renderer) override;

private:
	bool alive_{true};
};