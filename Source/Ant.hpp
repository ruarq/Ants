#pragma once

#include <limits>

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Object.hpp"
#include "TextureManager.hpp"
#include "Math.hpp"
#include "Random.hpp"
#include "Input.hpp"
#include "Food.hpp"
#include "Pheromone.hpp"

class Ant final : public Object
{
	enum class Direction
	{
		Straight, Left, Right
	};

public:
	static constexpr float maxSpeed = 50.0f;
	static constexpr float turnStrength = 50.0f;
	static constexpr float wanderStrength = 0.1f;

	static constexpr float viewRadius = 75.0f;
	static constexpr float pickUpRadius = 3.5f;

	static constexpr float pheromoneFrequency = 0.5f;

public:
	Ant();

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

	void SetVelocity(const sf::Vector2f &velocity);
	sf::Vector2f GetVelocity() const;

private:
	void HandleFood(const World &world);
	void HandlePheromones(World &world, const float deltaTime);

private:
	sf::Sprite antSprite;
	sf::Vector2f velocity;
	sf::Vector2f desiredDirection;

	Food *targetFood = nullptr;
	
	float pheromoneTimer = 0.0f;
};