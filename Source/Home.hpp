#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "World.hpp"

class Home final : public Object
{
public:
	Home();

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

private:
	sf::CircleShape shape;
};