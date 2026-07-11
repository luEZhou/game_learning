#include "Game.h"

#include "SDL3_image/SDL_image.h"

#include "Paddle.h"
#include "Brick.h"

bool Game::init()
{
	if (!initSDL()) {
		return false;
	}

	if (!loadResources()) {
		return false;
	}

	createLevel();

	running_ = true;

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
	float mx, my;

	SDL_GetMouseState(&mx, &my);

	exitHover_ =
			mx >= exitRect_.x &&
			mx <= exitRect_.x + exitRect_.w &&
			my >= exitRect_.y &&
			my <= exitRect_.y + exitRect_.h;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_EVENT_QUIT:
			running_ = false;
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (exitHover_) {
				running_ = false;
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

	renderBackground();
	renderObjects();
	renderUI();

	SDL_RenderPresent(renderer_);
}

bool Game::initSDL()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window_ = SDL_CreateWindow(
			"Game_learning", 1280.f, 720.f, 0);
	if (!window_) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, nullptr);
	if (!renderer_) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window_);
		return false;
	}

	return true;
}

bool Game::loadResources()
{

	if (!resources_.loadTexture(renderer_, "background", "assets/background.png")) {
		SDL_Log("Failed to load background texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "paddle", "assets/paddle.png")) {
		SDL_Log("Failed to load paddle texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "brick", "assets/brick_blue.png")) {
		SDL_Log("Failed to load brick texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "hud_top", "assets/ui/hud_top.png")) {
		SDL_Log("Failed to load hud_top texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "hud_bottom", "assets/ui/hud_bottom.png")) {
		SDL_Log("Failed to load hud_bottom texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "button_exit", "assets/ui/button_exit.png")) {
		SDL_Log("Failed to load button_exit texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "button_exit_hover", "assets/ui/button_exit_hover.png")) {
		SDL_Log("Failed to load button_exit_hover texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "heart", "assets/ui/heart.png")) {
		SDL_Log("Failed to load heart texture");
		return false;
	}

	if (!resources_.loadTexture(renderer_, "panel", "assets/ui/panel.png")) {
		SDL_Log("Failed to load panel texture");
		return false;
	}

	return true;
}

void Game::createLevel()
{
	createPaddle();
	createBricks();
}

void Game::createPaddle()
{
	spawn<Paddle>(
			resources_.getTexture("paddle"),
			(1280.0f - 100.0f) / 2.0f - 60.0f,
			720.0f - 25.0f - 45.0f, 120.0f, 20.0f, 300.0f);
}

void Game::createBricks()
{
	Texture2D* brick = resources_.getTexture("brick");

	constexpr int rows{5};
	constexpr int cols{10};
	constexpr float brickWidth{108.f};
	constexpr float brickHeight{32.f};
	// constexpr float gap{2.f};

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			spawn<Brick>(
					brick,
					100.f + col * brickWidth,
					75.f + row * brickHeight,
					brickWidth,
					brickHeight);
		}
	}
}

void Game::renderBackground()
{
	auto bg = resources_.getTexture("background");
	bg->draw(renderer_, {0, 0, 1280, 720});
}

void Game::renderObjects()
{
	for (auto& object : objects_) {
		object->render(renderer_);
	}
}

void Game::renderUI()
{
	resources_.getTexture("hud_top")->draw(renderer_, {0, 0, 1280, 70});

	resources_.getTexture("hud_bottom")->draw(renderer_, {0, 675, 1280, 45});

	auto* exitTexture = exitHover_
			? resources_.getTexture("button_exit_hover")
			: resources_.getTexture("button_exit");

	exitTexture->draw(renderer_, exitRect_);

	for (int i = 0; i < lives_; i++) {
		resources_.getTexture("heart")->draw(
				renderer_, {20.f + i * 40.f, 10.f, 32.f, 32.f});
	}
}