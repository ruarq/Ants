#pragma once

#include <SFML/Graphics.hpp>

namespace Input
{

void SetWindow(const sf::RenderWindow &window);
sf::Vector2f GetMousePos();

}