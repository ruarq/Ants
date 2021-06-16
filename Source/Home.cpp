#include "Home.hpp"

Home::Home()
{
	shape.setRadius(15.0f);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setFillColor(sf::Color(100, 100, 100));
}

void Home::Update(World &world, const float deltaTime)
{
}

void Home::Render(sf::RenderWindow &window)
{
	shape.setPosition(position);
	window.draw(shape);
}