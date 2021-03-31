#include "FoodSource.hpp"

void FoodSource::Create(World &world)
{
	std::vector<Food*> foodToSpawn = this->CreateFood();

	for (Food *food : foodToSpawn)
	{
		world.Spawn(food);
	}

	this->Kill();
}

void FoodSource::Update(World &world, const float dt)
{
}

void FoodSource::Render(olc::PixelGameEngine &context)
{
}

/**
 * Circular food source
 */
CircularFoodSource::CircularFoodSource(const unsigned foodAmount, const float radius)
	: foodAmount(foodAmount)
	, radius(radius)
{
}

std::vector<Food*> CircularFoodSource::CreateFood()
{
	std::vector<Food*> food;

	auto RandomPosition = [&]() -> olc::vf2d
	{
		const float randomDistance = RandomFloat(0.0f, radius);
		olc::vf2d randomDirection = RandomVector2D();

		// scale the random direction to the random distance
		randomDirection = randomDirection.norm() * randomDistance;

		return position + randomDirection;
	};

	for (unsigned i = 0; i < foodAmount; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(RandomPosition());

		food.push_back(newFood);
	}

	return food;
}