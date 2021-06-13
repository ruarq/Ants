#pragma once

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Object.hpp"

class Food final : public Object
{
public:
	Food();

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

private:
	sf::CircleShape shape;
};