#include "Pheromone.hpp"

Pheromone::Pheromone(const Type type)
	: type(type)
{
	shape.setRadius(1.0f);
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
			shape.setFillColor(sf::Color::Blue);
			break;

		case Pheromone::ToFood:
			shape.setFillColor(sf::Color::Red);
			break;
	}

	// window.draw(shape);
}

Pheromone::Type Pheromone::GetType() const
{
	return type;
}