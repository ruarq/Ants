#pragma once

#include "olcPixelGameEngine.h"

#include "GameObject.hpp"
#include "World.hpp"

enum class PheromoneType
{
	ToFood,
	ToHome
};

class Pheromone final : public GameObject
{
public:
	static constexpr float lifetime = 15.0f;

public:
	Pheromone(const PheromoneType type);

public:
	void Update(World &world, const float dt) override;
	void Render(olc::PixelGameEngine &context) override;

private:
	float timeLeftAlive;
	PheromoneType type;
};