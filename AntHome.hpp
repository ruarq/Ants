#pragma once

#include "olcPixelGameEngine.h"

#include "GameObject.hpp"
#include "Ant.hpp"

class AntHome final : public GameObject
{
public:
	AntHome(const unsigned numAnts);

public:
	void Create(World &world) override;
	void Update(World &world, const float dt) override;
	void Render(olc::PixelGameEngine &context) override;

private:
	const unsigned numAnts;
	unsigned foodCount;
};