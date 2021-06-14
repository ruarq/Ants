#include "Food.hpp"

Food::Food()
{
	shape.setRadius(2.5f);
	shape.setOrigin(sf::Vector2f(shape.getRadius() / 2.0f, shape.getRadius() / 2.0f));
	shape.setFillColor(sf::Color::Green);
}

void Food::Update(World &world, const float deltaTime)
{
}

void Food::Render(sf::RenderWindow &window)
{
	shape.setPosition(position);
	window.draw(shape);
}