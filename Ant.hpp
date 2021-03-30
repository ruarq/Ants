#pragma once

#include "olcPixelGameEngine.h"

#include "GameObject.hpp"
#include "Util.hpp"

class Ant final : public GameObject
{
public:
	static constexpr float speed = 20.0f;
	static constexpr float turnSpeed = 50.0f;

public:
	void Update(const float dt) override;

	void SetVelocity(const olc::vf2d &velocity);
	olc::vf2d GetVelocity() const;

private:
	void TurnRight(const float dt);
	void TurnLeft(const float dt);

private:
	olc::vf2d velocity;
};