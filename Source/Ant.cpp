#include "Ant.hpp"

Ant::Ant()
{
	// Create antSprite
	const sf::Texture &antTexture = TextureManager::GetTexture("Ant");
	antSprite.setTexture(antTexture);
	antSprite.setOrigin(static_cast<sf::Vector2f>(antTexture.getSize() / 2u));
	antSprite.setScale(sf::Vector2f(0.8f, 0.8f));

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

	// silly out of bounds check
	if (position.x + velocity.x <= 0.0f || position.y + velocity.y <= 0.0f || position.x + velocity.x >= 1280.0f || position.y + velocity.y >= 720.0f)
	{
		velocity *= -1.0f;
		desiredDirection = Normalized(velocity);
	}
}

void Ant::Render(sf::RenderWindow &window)
{
	// Draw the antSprite
	antSprite.setPosition(position);
	antSprite.setRotation(Angle(velocity));
	window.draw(antSprite);

	// #if defined(DEBUG)
	// sf::CircleShape viewCircle(viewRadius);
	// viewCircle.setFillColor(sf::Color::Transparent);
	// viewCircle.setOutlineColor(sf::Color::Blue);
	// viewCircle.setOutlineThickness(1.0f);
	// viewCircle.setPosition(position);
	// viewCircle.setOrigin(sf::Vector2f(viewRadius, viewRadius));
	// window.draw(viewCircle);
	// #endif
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
		const std::vector<Food*> allFood = world.GetAllObjectsOfType<Food>();

		if (!allFood.empty())
		{
			// Find the closest food
			auto closestFoodItr = std::min_element(allFood.begin(), allFood.end(), [&](Food *a, Food *b)
			{
				return Length(a->GetPosition() - position) < Length(b->GetPosition() - position);
			});

			if (this->IsInView((*closestFoodItr)->GetPosition()) && (*closestFoodItr)->IsAvailable())
			{
				targetFood = *closestFoodItr;
				targetFood->SetAvailable(false);
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
			targetFood->SetPosition(position);

			this->FollowPheromones(world, Pheromone::ToHome);

			// Search for ant homes to drop the food off
			const std::vector<Home*> antHomes = world.GetAllObjectsOfType<Home>();
			for (Home *home : antHomes)
			{
				if (this->IsInView(home->GetPosition()))
				{
					desiredDirection = Normalized(home->GetPosition() - position);
				}
				else if (Length(home->GetPosition() - position) <= pickUpRadius)
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
		else if (Length(targetFood->GetPosition() - position) <= pickUpRadius)
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

	const std::vector<Pheromone*> allPheromones = world.GetAllObjectsOfType<Pheromone>();
	for (Pheromone *pheromone : allPheromones)
	{
		if (pheromone->GetType() == type && this->IsInView(pheromone->GetPosition()))
		{
			pheromonePositions.push_back(pheromone->GetPosition());
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
	velocity *= 0.5f;
	desiredDirection *= -1.0f;
}