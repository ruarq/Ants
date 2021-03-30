#include "Ant.hpp"

void Ant::Update(const float dt)
{
	if (velocity.mag() > 0.0f)
		velocity = velocity.norm() * speed;
	else
		velocity = RandomVector2D();

	// make a turn with a probability of 5%
	if (std::rand() % 101 <= 5)
	{
		// turn left or right with p=50%
		if (std::rand() % 101 <= 50)
		{
			this->TurnLeft(dt);
		}
		else
		{
			this->TurnRight(dt);
		}
	}

	position += velocity * dt;
}

void Ant::SetVelocity(const olc::vf2d &velocity)
{
	this->velocity = velocity;
}

olc::vf2d Ant::GetVelocity() const
{
	return velocity;
}

void Ant::TurnRight(const float dt)
{
	const olc::vf2d direction(velocity.y, -velocity.x);
	const olc::vf2d turnVelocity = velocity - direction;
	velocity += turnVelocity * turnSpeed * dt;
}

void Ant::TurnLeft(const float dt)
{
	const olc::vf2d direction(-velocity.y, velocity.x);
	const olc::vf2d turnVelocity = velocity - direction;
	velocity += turnVelocity * turnSpeed * dt;
}