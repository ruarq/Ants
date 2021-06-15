#include "Input.hpp"

namespace Input
{

const sf::RenderWindow *window = nullptr;

void SetWindow(const sf::RenderWindow &window)
{
	Input::window = &window;
}

sf::Vector2f GetMousePos()
{
	if (window)
	{
		return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	}
	else
	{
		return sf::Vector2f();
	}
}

}