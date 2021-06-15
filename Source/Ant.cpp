#include "Ant.hpp"

#include <iostream>

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
	const sf::Vector2f target = FindTarget(world);
	this->MoveTowards(target, deltaTime);
}

void Ant::Render(sf::RenderWindow &window)
{
	// Draw the antSprite
	antSprite.setPosition(position);
	antSprite.setRotation(Angle(velocity));
	window.draw(antSprite);

	#if defined(DEBUG)
	sf::CircleShape viewCircle(viewRadius);
	viewCircle.setFillColor(sf::Color::Transparent);
	viewCircle.setOutlineColor(sf::Color::Blue);
	viewCircle.setOutlineThickness(1.0f);
	viewCircle.setPosition(position);
	viewCircle.setOrigin(sf::Vector2f(viewRadius, viewRadius));
	window.draw(viewCircle);
	#endif
}

void Ant::SetVelocity(const sf::Vector2f &velocity)
{
	this->velocity = velocity;
}

sf::Vector2f Ant::GetVelocity() const
{
	return velocity;
}

/**
 * @note Thanks to Sebastian Lague for sharing his Ant movement script. I like it a lot!
 */
void Ant::MoveTowards(const sf::Vector2f &target, const float deltaTime)
{
	const sf::Vector2f dirToTarget = Normalized(target - position);
	const sf::Vector2f desiredVelocity = dirToTarget * maxSpeed;
	const sf::Vector2f desiredTurnForce = (desiredVelocity - velocity) * turnStrength;
	const sf::Vector2f acceleration = Clamp(desiredTurnForce, turnStrength);

	velocity = Clamp(velocity + acceleration * deltaTime, maxSpeed);
	position += velocity * deltaTime;
}

sf::Vector2f Ant::FindTarget(const World &world)
{
	sf::Vector2f target;
	bool foundTarget = false;

	// Try to find food
	float closestDistanceToFood = std::numeric_limits<float>::max();
	const std::vector<Food*> foodObjects = world.GetAllObjectsOfType<Food>();

	for (Food *food : foodObjects)
	{
		const float distance = Length(food->GetPosition() - position);

		if (distance <= viewRadius && distance < closestDistanceToFood)
		{
			foundTarget = true;
			target = food->GetPosition();
		}
	}

	if (foundTarget)
	{
		return target;
	}
	
	// Move to some random location in the view radius if no target was found
	auto randomDir = []()
	{
		return RandomVec2d() * Random(viewRadius / 2.0f, viewRadius);
	};

	const float distanceToRandomTarget = Length(randomTarget - position);
	if (distanceToRandomTarget < viewRadius / 2.0f || distanceToRandomTarget > viewRadius)
	{
		randomTarget = position + randomDir();
	}

	return randomTarget;
}