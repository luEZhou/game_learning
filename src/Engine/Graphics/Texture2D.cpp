#include "Texture2D.h"

#include "SDL3_image/SDL_image.h"

#include "Math/Vector2.h"

Texture2D::Texture2D(Texture2D&& other) noexcept
{
	texture_ = other.texture_;
	width_ = other.width_;
	height_ = other.height_;

	other.texture_ = nullptr;
	other.width_ = 0.0f;
	other.height_ = 0.0f;
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
	if (this != &other) {
		unload();

		texture_ = other.texture_;
		width_ = other.width_;
		height_ = other.height_;

		other.texture_ = nullptr;
		other.width_ = 0.0f;
		other.height_ = 0.0f;
	}
	return *this;
}

Texture2D::~Texture2D()
{
	unload();
}

bool Texture2D::load(SDL_Renderer* renderer, std::string_view path)
{
	unload();

	SDL_Surface* surface = IMG_Load(path.data());

	if (nullptr == surface) {
		SDL_Log("Failed to load image: %s", SDL_GetError());
		return false;
	}

	width_ = static_cast<float>(surface->w);
	height_ = static_cast<float>(surface->h);

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	if (nullptr == texture_) {
		SDL_Log("Failed to create texture: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Texture2D::draw(
		SDL_Renderer* renderer,
		const Vector2& position) const
{
	if (nullptr == texture_) {
		return;
	}

	SDL_FRect dst{
			position.X(),
			position.Y(),
			width_,
			height_};

	SDL_RenderTexture(renderer, texture_, nullptr, &dst);
}

void Texture2D::unload()
{
	if (nullptr != texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
	width_ = 0.0f;
	height_ = 0.0f;
}

void Texture2D::draw(
		SDL_Renderer* renderer,
		const SDL_FRect& dst) const
{
	if (nullptr == texture_) {
		return;
	}

	SDL_RenderTexture(renderer, texture_, nullptr, &dst);
}

float Texture2D::width() const
{
	return width_;
}

float Texture2D::height() const
{
	return height_;
}

bool Texture2D::isLoaded() const
{
	return nullptr != texture_;
}