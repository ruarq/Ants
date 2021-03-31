#pragma once

#include "olcPixelGameEngine.h"

#include "World.hpp"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

public:
	virtual void Create(World &world) {};
	virtual void Update(World &world, const float dt) = 0;
	virtual void Render(olc::PixelGameEngine &context) = 0;

public:
	void SetPosition(const olc::vf2d &position);
	olc::vf2d GetPosition() const;

	void Kill();
	bool IsAlive() const;

protected:
	olc::vf2d position;

private:
	bool alive;
};