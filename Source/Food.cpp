#include "Food.hpp"

Food::Food()
{
	shape.setRadius(2.5f);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
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

void Food::SetAvailable(const bool isAvailable)
{
	this->isAvailable = isAvailable;
}

bool Food::IsAvailable() const
{
	return isAvailable;
}