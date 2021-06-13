#pragma once

#include "World.hpp"
#include "Object.hpp"

class Ant final : public Object
{
public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;
};