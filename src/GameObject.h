#pragma once

struct SDL_Renderer;

class GameObject {

public:
	GameObject(float x, float y, float width, float height) :
		x_(x), y_(y), width_(width), height_(height) {}

	virtual ~GameObject() {}

	float getX() const { return x_; }
	float getY() const { return y_; }
	float getWidth() const { return width_; }
	float getHeight() const { return height_; }

	virtual void update(float dt) = 0;

	virtual void render(SDL_Renderer* renderer) = 0;

protected:
	float x_;
	float y_;
	float width_;
	float height_;
};