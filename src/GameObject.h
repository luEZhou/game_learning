#pragma once

#include "Math/Vector2.h"
#include "Graphics/Texture2D.h"

struct SDL_Renderer;

class GameObject {

public:
	GameObject(
			Texture2D* texture,
			float x,
			float y,
			float width,
			float height) :
		texture_(texture),
		position_(x, y),
		width_(width),
		height_(height) {}

	virtual ~GameObject() {}

	Vector2 position() const { return position_; }

	float getWidth() const { return width_; }
	float getHeight() const { return height_; }

	virtual void update(float dt) = 0;

	virtual void render(SDL_Renderer* renderer);

protected:
	Vector2 position_;
	Texture2D* texture_;
	float width_;
	float height_;
};