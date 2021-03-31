#include "Ant.hpp"

Ant::Ant()
	: pheromoneTimer(pheromoneSpawnDelay)
	, currentFood(nullptr)
	, carriesFood(false)
{
}

void Ant::Update(World &world, const float dt)
{
	this->Move(dt);
	this->SpawnPheromones(world, dt);

	// Handle food related stuff
	this->SearchFood(world);
	this->PickupFood(dt);
	this->CarryFood(dt);
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

void Ant::Move(const float dt)
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

void Ant::SpawnPheromones(World &world, const float dt)
{
	// Update the pheromone timer
	pheromoneTimer -= dt;
	if (pheromoneTimer <= 0.0f)
	{
		PheromoneType pheromoneType;
		if (carriesFood)
		{
			pheromoneType = PheromoneType::ToFood;
		}
		else
		{
			pheromoneType = PheromoneType::ToHome;
		}

		Pheromone *pheromone = new Pheromone(pheromoneType);
		pheromone->SetPosition(position);

		world.Spawn(pheromone);

		pheromoneTimer = pheromoneSpawnDelay;
	}
}

void Ant::SearchFood(const World &world)
{
	if (currentFood != nullptr)
		return;

	std::vector<GameObject*> gameObjects = world.GetAllObjects();

	for (GameObject *gameObject : gameObjects)
	{
		if (Food *food = dynamic_cast<Food*>(gameObject))
		{
			const olc::vf2d toFood = (food->GetPosition() - position);

			// if the food it within the viewRadius range and inside the fielOfView
			if (toFood.mag() <= viewRadius && Angle(velocity, toFood) <= fieldOfView)
			{
				currentFood = food;
				break;
			}
		}
	}
}

void Ant::PickupFood(const float dt)
{
	if (currentFood && !carriesFood)
	{
		const olc::vf2d toFood = (currentFood->GetPosition() - position);

		// steer towards the food
		const olc::vf2d turnVelocity = toFood - velocity;
		velocity += turnVelocity * turnSpeed * dt;

		// let the CarryFood() function take over
		if (toFood.mag() <= pickupRadius)
		{
			carriesFood = true;
		}
	}
}

void Ant::CarryFood(const float dt)
{
}