#pragma once

#include <SFML/Graphics.hpp>

#include "ApplicationState.hpp"
#include "World.hpp"
#include "Ant.hpp"
#include "Food.hpp"

class ApplicationStateRunning final : public ApplicationState
{
public:
	ApplicationStateRunning();

public:
	ApplicationState* Update(const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

private:
	World world;
};