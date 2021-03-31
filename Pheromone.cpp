#include "Pheromone.hpp"

Pheromone::Pheromone(const PheromoneType type)
	: timeLeftAlive(lifetime)
	, type(type)
{
}

void Pheromone::Update(World &world, const float dt)
{
	timeLeftAlive -= dt;
	if (timeLeftAlive <= 0.0f)
		this->Kill();
}

void Pheromone::Render(olc::PixelGameEngine &context)
{
	olc::Pixel color;

	switch (type)
	{
		case PheromoneType::ToHome:
			color = olc::BLUE;
			break;

		case PheromoneType::ToFood:
			color = olc::RED;
			break;

		default:
			color = olc::BLUE;
			break;
	}

	context.FillCircle(position, 1.5f, color);
}