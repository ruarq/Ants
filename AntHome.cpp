#include "AntHome.hpp"

AntHome::AntHome(const unsigned numAnts)
	: numAnts(numAnts)
{
}

void AntHome::Create(World &world)
{
	for (unsigned i = 0; i < numAnts; i++)
	{
		Ant *ant = new Ant();
		ant->SetPosition(position);

		world.Spawn(ant);
	}
}

void AntHome::Update(World &world, const float dt)
{
}

void AntHome::Render(olc::PixelGameEngine &context)
{
	context.DrawCircle(position, 15.0f);
}