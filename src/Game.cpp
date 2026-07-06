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
	return true;
}

void Game::shutdown()
{
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
	const bool* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_W]) {
		player_.y -= player_.speed * dt;
	}
	if (state[SDL_SCANCODE_S]) {
		player_.y += player_.speed * dt;
	}
	if (state[SDL_SCANCODE_A]) {
		player_.x -= player_.speed * dt;
	}
	if (state[SDL_SCANCODE_D]) {
		player_.x += player_.speed * dt;
	}

	if (player_.x < 0.0f)
		player_.x = 0.0f;
	if (player_.x > 1280.0f - 50.0f)
		player_.x = 1280.0f - 50.0f;
	if (player_.y < 0.0f)
		player_.y = 0.0f;
	if (player_.y > 720.0f - 50.0f)
		player_.y = 720.0f - 50.0f;
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	SDL_FRect playerRect = {player_.x, player_.y, 50.0f, 50.0f};
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer_, &playerRect);

	SDL_FRect quitButtonRect = {1150.0f, 20.0f, 100.0f, 40.0f};
	SDL_SetRenderDrawColor(renderer_, 150, 150, 150, 255);
	SDL_RenderFillRect(renderer_, &quitButtonRect);

	SDL_RenderPresent(renderer_);
}
