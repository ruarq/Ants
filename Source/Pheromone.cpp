#include "Pheromone.hpp"

Pheromone::Pheromone(const Type type)
	: type(type)
{
	shape.setRadius(0.5f);
}

void Pheromone::Update(World &world, const float deltaTime)
{
	timeAlive += deltaTime;
	if (timeAlive >= lifeTime)
	{
		this->SetAlive(false);
	}
}

void Pheromone::Render(sf::RenderWindow &window)
{
	shape.setPosition(position);

	switch (type)
	{
		case Pheromone::ToHome:
			shape.setFillColor(sf::Color(90, 90, 180)); // Blue
			break;

		case Pheromone::ToFood:
			shape.setFillColor(sf::Color(120, 60, 60)); // Red
			break;
	}

	window.draw(shape);
}

Pheromone::Type Pheromone::GetType() const
{
	return type;
}