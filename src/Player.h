#pragma once

#include "GameObject.h"

class Player : public GameObject {

public:
	Player(float x, float y, float width, float height, float speed) :
		GameObject(x, y, width, height),
		speed_(speed) {}

	virtual ~Player() {}

	void update(float dt) override;

	void render(SDL_Renderer* renderer) override;

private:
	float speed_;
};