#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Object.hpp"
#include "TextureManager.hpp"
#include "Math.hpp"
#include "Random.hpp"

class Ant final : public Object
{
	enum class Direction
	{
		Straight, Left, Right
	};

public:
	static constexpr float maxSpeed = 15.0f;
	static constexpr float acceleration = 5.0f;

	static constexpr float turnSpeed = 25.0f;
	static constexpr float turnFrequency = 15.0f;

public:
	Ant();

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

	void SetVelocity(const sf::Vector2f &velocity);
	sf::Vector2f GetVelocity() const;

private:
	void Move(const Direction dir, const float deltaTime);
	void TurnRandom(const float deltaTime);

private:
	sf::Sprite antSprite;
	sf::Vector2f velocity;

	float turnTimer = 1.0f / turnFrequency;
};