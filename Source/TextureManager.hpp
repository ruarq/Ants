#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

class TextureManager final
{
public:
	static void AddTexture(const std::string &alias, const sf::Texture &texture);
	static const sf::Texture& GetTexture(const std::string &alias);

private:
	static std::unordered_map<std::string, sf::Texture> textures;
};