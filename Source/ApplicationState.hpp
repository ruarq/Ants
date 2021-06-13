#pragma once

#include <SFML/Graphics.hpp>

class ApplicationState
{
public:
	virtual ~ApplicationState() = default;

public:
	virtual ApplicationState* Update(const float deltaTime) = 0;
	virtual void Render(sf::RenderWindow &window) = 0;
};