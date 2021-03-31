#pragma once

#include "GameObject.hpp"
#include "Food.hpp"
#include "Util.hpp"

/**
 * The food source will deploy the foodAmount into the world and then kill itself.
 * It is just a mechanism to spawn food rather than a actual object.
 */
class FoodSource : public GameObject
{
public:
	void Create(World &world) final override;
	void Update(World &world, const float dt) final override;
	void Render(olc::PixelGameEngine &context) final override;

protected:
	virtual std::vector<Food*> CreateFood() = 0;
};

// Some default food sources
class CircularFoodSource final : public FoodSource
{
public:
	CircularFoodSource(const unsigned foodAmount, const float radius);

private:
	std::vector<Food*> CreateFood() override;

private:
	unsigned foodAmount;
	float radius;
};