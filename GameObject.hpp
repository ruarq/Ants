#pragma once

#include "olcPixelGameEngine.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

public:
	virtual void Update(const float dt) = 0;

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