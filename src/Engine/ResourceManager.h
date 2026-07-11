#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Graphics/Texture2D.h"

struct SDL_Renderer;

class ResourceManager {

	using TextureMap = std::unordered_map<std::string, std::unique_ptr<Texture2D>>;

public:
	ResourceManager() = default;
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourceManager(ResourceManager&&);
	ResourceManager& operator=(ResourceManager&&);

	bool loadTexture(
			SDL_Renderer* renderer,
			const std::string& id,
			const std::string& path);

	Texture2D* getTexture(const std::string& id);

	void clear();

private:
	TextureMap textures_;
};