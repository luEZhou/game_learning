#pragma once

#include "Player.h"
#include <memory>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;

class Game {

public:
	bool init();

	void run();

	void shutdown();

private:
	void process_input();

	void update(float dt);

	void render();

private:
	bool running_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	std::vector<std::unique_ptr<GameObject>> objects_;
};