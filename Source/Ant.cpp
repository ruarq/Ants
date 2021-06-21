#include "Ant.hpp"

Ant::Ant()
{
	// Create antSprite
	const sf::Texture &antTexture = TextureManager::GetTexture("Ant");
	antSprite.setTexture(antTexture);
	antSprite.setOrigin(static_cast<sf::Vector2f>(antTexture.getSize() / 2u));
	antSprite.setScale(0.5f, 0.5f);

	velocity = RandomVec2d();
}

void Ant::Update(World &world, const float deltaTime)
{
	this->HandleFood(world);
	this->HandlePheromones(world, deltaTime);

	desiredDirection = Normalized(desiredDirection + RandomVec2d() * wanderStrength);
	const sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
	const sf::Vector2f desiredTurnForce = (desiredVelocity - velocity) * turnStrength;
	const sf::Vector2f acceleration = Clamp(desiredTurnForce, turnStrength);

	velocity = Clamp(velocity + acceleration * deltaTime, maxSpeed);
	position += velocity * deltaTime;

	// Just wrap the ants position for now (weird flex)
	if (position.x < 0.0f) position.x = 1280.0f;
	if (position.x > 1280.0f) position.x = 0.0f;
	if (position.y < 0.0f) position.y = 720.0f;
	if (position.y > 720.0f) position.y = 0.0f;
}

void Ant::Render(sf::RenderWindow &window)
{
	// Draw the antSprite
	antSprite.setPosition(position);
	antSprite.setRotation(Angle(velocity));
	window.draw(antSprite);
}

void Ant::SetVelocity(const sf::Vector2f &velocity)
{
	this->velocity = velocity;
}

sf::Vector2f Ant::GetVelocity() const
{
	return velocity;
}

void Ant::HandleFood(const World &world)
{
	if (!targetFood)
	{
		std::vector<Object*> neighbors = world.Query(position, viewRadius);
		std::remove_if(neighbors.begin(), neighbors.end(), [](Object *object)
		{
			return !dynamic_cast<Food*>(object);
		});

		if (!neighbors.empty())
		{
			// Find the closest food
			auto closestNeighbor = std::min_element(neighbors.begin(), neighbors.end(), [&](Object *a, Object *b)
			{
				return Length(a->GetPosition() - position) < Length(b->GetPosition() - position);
			});

			if (Food *closestFood = dynamic_cast<Food*>(*closestNeighbor))
			{
				if (this->IsInView(closestFood->GetPosition()) && closestFood->IsAvailable())
				{
					targetFood = closestFood;
					targetFood->SetAvailable(false);
				}
			}
		}

		// If the ant did not find any food, it will try to find pheromones (ToFood pheromones to be specific) to follow
		if (!targetFood)
		{
			this->FollowPheromones(world, Pheromone::ToFood);
		}
	}
	else
	{
		if (carriesFood)
		{
			targetFood->SetPosition(position + Normalized(velocity) * interactionRadius);

			this->FollowPheromones(world, Pheromone::ToHome);

			// Search for ant homes to drop the food off
			for (Object *object : world.Query(position, viewRadius))
			{
				if (Home *home = dynamic_cast<Home*>(object))
				{
					if (this->IsInView(home->GetPosition()))
					{
						desiredDirection = Normalized(home->GetPosition() - position);
					}
					else if (Length(home->GetPosition() - position) <= interactionRadius)
					{
						// TODO:
						// home->AddFood(targetFood);
						targetFood->SetAlive(false);
						targetFood = nullptr;
						carriesFood = false;

						this->TurnAround();
					}
				}
			}
		}
		else if (Length(targetFood->GetPosition() - position) <= interactionRadius)
		{
			carriesFood = true;
			this->TurnAround();
		}
		else
		{
			desiredDirection = Normalized(targetFood->GetPosition() - position);
		}
	}
}

void Ant::HandlePheromones(World &world, const float deltaTime)
{
	pheromoneTimer += deltaTime;
	if (pheromoneTimer >= 1.0f / pheromoneFrequency)
	{
		pheromoneTimer = 0.0f;

		// Choose pheromone type to excrete
		Pheromone::Type type;
		if (!carriesFood)
		{
			type = Pheromone::ToHome;
		}
		else
		{
			type = Pheromone::ToFood;
		}

		Pheromone *newPheromone = new Pheromone(type);
		newPheromone->SetPosition(position);
		world.AddObject(newPheromone);
	}
}

void Ant::FollowPheromones(const World &world, const Pheromone::Type type)
{
	std::vector<sf::Vector2f> pheromonePositions;

	for (Object *object : world.Query(position, viewRadius))
	{
		if (Pheromone *pheromone = dynamic_cast<Pheromone*>(object))
		{
			if (pheromone->GetType() == type && this->IsInView(pheromone->GetPosition()))
			{
				pheromonePositions.push_back(pheromone->GetPosition());
			}
		}
	}

	if (!pheromonePositions.empty())
	{
		const sf::Vector2f averagePosition = std::accumulate(
			pheromonePositions.begin(), pheromonePositions.end(), sf::Vector2f())
			/ static_cast<float>(pheromonePositions.size());

		desiredDirection = Normalized(averagePosition - position);
	}
}

bool Ant::IsInView(const sf::Vector2f &position) const
{
	const sf::Vector2f toPosition = position - this->position;

	// Something is in view, if ...
	return
		// the position is inside the viewRadius
		(Length(toPosition) <= viewRadius
		// the angle to the object is within the viewAngle
		&& Angle(toPosition, this->velocity) <= viewAngle / 2.0f);
}

void Ant::TurnAround()
{
	velocity *= -1.0f;
	desiredDirection *= -1.0f;
}