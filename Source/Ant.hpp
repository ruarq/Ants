#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Object.hpp"
#include "TextureManager.hpp"
#include "Math.hpp"

class Ant final : public Object
{
public:
	Ant();

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

	void SetVelocity(const sf::Vector2f &velocity);
	sf::Vector2f GetVelocity() const;

private:
	sf::Sprite antSprite;
	sf::Vector2f velocity;
};