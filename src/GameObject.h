#pragma once

#include "Math/Vector2.h"

struct SDL_Renderer;

class GameObject {

public:
	GameObject(float x, float y, float width, float height) :
		position_(x, y), width_(width), height_(height) {}

	virtual ~GameObject() {}

	Vector2 position() const { return position_; }

	float getWidth() const { return width_; }
	float getHeight() const { return height_; }

	virtual void update(float dt) = 0;

	virtual void render(SDL_Renderer* renderer) = 0;

protected:
	Vector2 position_;
	float width_;
	float height_;
};