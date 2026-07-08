#include "Game.h"

#include "SDL3/SDL.h"

bool Game::init()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return false;
	}
	window_ = SDL_CreateWindow("Game_learning", 1280, 720, 0);
	if (!window_) {
		return false;
	}
	renderer_ = SDL_CreateRenderer(window_, nullptr);
	if (!renderer_) {
		SDL_DestroyWindow(window_);
		return false;
	}
	running_ = true;

	objects_.push_back(std::make_unique<Player>(100.0f, 100.0f, 50.0f, 50.0f, 300.0f));

	return true;
}

void Game::shutdown()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::run()
{
	// last frame time
	Uint64 last_time = SDL_GetTicks();

	while (running_) {
		Uint64 current_time = SDL_GetTicks();
		float dt = (current_time - last_time) / 1000.0f;
		last_time = current_time;

		process_input();
		update(dt);
		render();
	}
	shutdown();
}

void Game::process_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_EVENT_QUIT:
			running_ = false;
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				float mouseX = event.button.x;
				float mouseY = event.button.y;
				if (mouseX >= 1150.0f && mouseX <= 1250.0f && mouseY >= 20.0f && mouseY <= 60.0f) {
					running_ = false;
				}
			}
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE) {
				running_ = false;
			}
			break;
		}
	}
}

void Game::update(float dt)
{

	for (auto& object : objects_) {
		object->update(dt);
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	for (auto& object : objects_) {
		object->render(renderer_);
	}

	SDL_FRect quitButtonRect = {1150.0f, 20.0f, 100.0f, 40.0f};
	SDL_SetRenderDrawColor(renderer_, 150, 150, 150, 255);
	SDL_RenderFillRect(renderer_, &quitButtonRect);

	SDL_RenderPresent(renderer_);
}
