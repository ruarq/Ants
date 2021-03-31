#include "Food.hpp"

void Food::Update(World &world, const float dt)
{
}

void Food::Render(olc::PixelGameEngine &context)
{
	context.FillCircle(position, 1.5f, olc::GREEN);
}