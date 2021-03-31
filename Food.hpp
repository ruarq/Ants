#pragma once

#include "olcPixelGameEngine.h"

#include "World.hpp"
#include "GameObject.hpp"

class Food final : public GameObject
{
public:
	void Update(World &world, const float dt) override;
	void Render(olc::PixelGameEngine &context) override;
};