#pragma once

#include "olcPixelGameEngine.h"

#include "GameObject.hpp"
#include "Pheromone.hpp"
#include "Food.hpp"
#include "World.hpp"
#include "Util.hpp"

class Ant final : public GameObject
{
public:
	static constexpr float speed = 20.0f;
	static constexpr float turnSpeed = 50.0f;
	static constexpr float pheromoneSpawnDelay = 1.0f;
	static constexpr float viewRadius = 50.0f;
	static constexpr float fieldOfView = 45.0f;
	static constexpr float pickupRadius = 2.5f;

public:
	Ant();

public:
	void Update(World &world, const float dt) override;
	void Render(olc::PixelGameEngine &context) override;

	void SetVelocity(const olc::vf2d &velocity);
	olc::vf2d GetVelocity() const;

private:
	void Move(const float dt);
	void TurnRight(const float dt);
	void TurnLeft(const float dt);

	void SpawnPheromones(World &world, const float dt);

	void SearchFood(const World &world);
	void PickupFood(const float dt);
	void CarryFood(const float dt);

private:
	olc::vf2d velocity;
	float pheromoneTimer;

	Food *currentFood;
	bool carriesFood;
};