#include "ResourceManager.h"

ResourceManager::ResourceManager(ResourceManager&& other) :
	textures_(std::move(other.textures_))
{
}

ResourceManager& ResourceManager::operator=(ResourceManager&& other)
{
	if (this != &other) {
		textures_ = std::move(other.textures_);
	}
	return *this;
}

bool ResourceManager::loadTexture(
		SDL_Renderer* renderer,
		const std::string& id,
		const std::string& path)
{
	auto texture = std::make_unique<Texture2D>();
	if (!texture->load(renderer, path)) {
		return false;
	}
	textures_[id] = std::move(texture);
	return true;
}

Texture2D* ResourceManager::getTexture(const std::string& id)
{
	auto it = textures_.find(id);
	if (it == textures_.end()) {
		return nullptr;
	}
	return it->second.get();
}

void ResourceManager::clear()
{
	textures_.clear();
}