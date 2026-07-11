#pragma once

struct SDL_Renderer;
struct SDL_FRect;
struct SDL_Texture;
class Vector2;

#include <string_view>

class Texture2D {

public:
	Texture2D() = default;
	~Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D(Texture2D&& other) noexcept;
	Texture2D& operator=(Texture2D&& other) noexcept;

	bool load(SDL_Renderer* renderer, std::string_view path);

	void unload();

	void draw(SDL_Renderer* renderer, const SDL_FRect& dst) const;

	void draw(SDL_Renderer* renderer, const Vector2& position) const;

	[[nodiscard]]
	float width() const;

	[[nodiscard]]
	float height() const;

	[[nodiscard]]
	bool isLoaded() const;

private:
	SDL_Texture* texture_{nullptr};

	float width_{};
	float height_{};
};