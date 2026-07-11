#pragma once

#include <memory>
#include <vector>

#include "SDL3/SDL.h"

#include "GameObject.h"
#include "ResourceManager.h"

class Game {

public:
	bool init();

	void run();

	void shutdown();

	~Game() = default;

	template <typename T, typename... Args>
	T* spawn(Args&&... args)
	{
		auto object = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = object.get();
		objects_.push_back(std::move(object));
		return ptr;
	}

private:
	void process_input();

	void update(float dt);

	void render();

	bool initSDL();

	bool loadResources();

	void createLevel();

	void createPaddle();

	void createBricks();

	void renderBackground();

	void renderObjects();

	void renderUI();

private:
	bool running_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	ResourceManager resources_;

	std::vector<std::unique_ptr<GameObject>> objects_;

	SDL_FRect exitRect_{1060.f, 0.f, 220.f, 70.f};

	bool exitHover_{false};

	int score_{0};
	int lives_{3};
};