#include "Ant.hpp"

Ant::Ant()
	: pheromoneTimer(pheromoneSpawnDelay)
{
}

void Ant::Update(World &world, const float dt)
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

	// Update the pheromone timer
	pheromoneTimer -= dt;
	if (pheromoneTimer <= 0.0f)
	{
		Pheromone *pheromone = new Pheromone(PheromoneType::ToHome);
		pheromone->SetPosition(position);
		
		world.Spawn(pheromone);

		pheromoneTimer = pheromoneSpawnDelay;
	}

	position += velocity * dt;
}

void Ant::Render(olc::PixelGameEngine &context)
{
	context.FillCircle(position, 1.5f);
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