#pragma once

#include "olcPixelGameEngine.h"

#include "GameObject.hpp"
#include "Pheromone.hpp"
#include "World.hpp"
#include "Util.hpp"

class Ant final : public GameObject
{
public:
	static constexpr float speed = 20.0f;
	static constexpr float turnSpeed = 50.0f;
	static constexpr float pheromoneSpawnDelay = 1.0f;

public:
	Ant();

public:
	void Update(World &world, const float dt) override;
	void Render(olc::PixelGameEngine &context) override;

	void SetVelocity(const olc::vf2d &velocity);
	olc::vf2d GetVelocity() const;

private:
	void TurnRight(const float dt);
	void TurnLeft(const float dt);

private:
	olc::vf2d velocity;
	float pheromoneTimer;
};