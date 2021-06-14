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
	this->TurnRandom(deltaTime);

	if (Length(velocity) >= maxSpeed)
	{
		velocity = Normalized(velocity) * maxSpeed;
	}

	position += velocity * deltaTime;
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

void Ant::Move(const Direction dir, const float deltaTime)
{
	sf::Vector2f acceleration;

	switch (dir)
	{
		case Direction::Left:
		{
			acceleration = Normalized(sf::Vector2f(velocity.y, -velocity.x)) * this->acceleration * turnSpeed;
		} break;

		case Direction::Right:
		{
			acceleration = Normalized(sf::Vector2f(-velocity.y, velocity.x)) * this->acceleration * turnSpeed;

		} break;

		case Direction::Straight:
		{
			acceleration = Normalized(velocity) * this->acceleration;
		} break;
	}

	velocity += acceleration * deltaTime;
}

void Ant::TurnRandom(const float deltaTime)
{
	turnTimer -= deltaTime;
	
	if (turnTimer <= 0.0f)
	{
		turnTimer = 1.0f / turnFrequency;

		if (Random() < 0.5f)
		{
			Move(Direction::Left, deltaTime);
		}
		else
		{
			Move(Direction::Right, deltaTime);
		}
	}
	else
	{
		Move(Direction::Straight, deltaTime);
	}
}