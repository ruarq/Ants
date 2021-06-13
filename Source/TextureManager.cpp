#include "TextureManager.hpp"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::AddTexture(const std::string &alias, const sf::Texture &texture)
{
	textures.emplace(alias, texture);
}

const sf::Texture& TextureManager::GetTexture(const std::string &alias)
{
	return textures.at(alias);
}