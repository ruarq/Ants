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

	desiredDirection = Normalized(desiredDirection + RandomVec2d() * wanderStrength);
	const sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
	const sf::Vector2f desiredTurnForce = (desiredVelocity - velocity) * turnStrength;
	const sf::Vector2f acceleration = Clamp(desiredTurnForce, turnStrength);

	velocity = Clamp(velocity + acceleration * deltaTime, maxSpeed);
	position += velocity * deltaTime;
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

			if (Length((*closestFoodItr)->GetPosition() - position) <= viewRadius && (*closestFoodItr)->IsAvailable())
			{
				targetFood = *closestFoodItr;
				targetFood->SetAvailable(false);
			}
		}
	}
	else
	{
		desiredDirection = Normalized(targetFood->GetPosition() - position);

		if (Length(targetFood->GetPosition() - position) <= pickUpRadius)
		{
			targetFood->SetAlive(false);
			targetFood = nullptr;
		}
	}
}