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

class Ant final : public Object
{
	enum class Direction
	{
		Straight, Left, Right
	};

public:
	static constexpr float maxSpeed = 125.0f;
	static constexpr float turnStrength = 125.0f;

	static constexpr float viewRadius = 75.0f;

public:
	Ant();

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

	void SetVelocity(const sf::Vector2f &velocity);
	sf::Vector2f GetVelocity() const;

private:
	/**
	 * @brief Let the ant move towards a certain target
	 */
	void MoveTowards(const sf::Vector2f &target, const float deltaTime);
	sf::Vector2f FindTarget(const World &world);

private:
	sf::Sprite antSprite;
	sf::Vector2f velocity;

	sf::Vector2f randomTarget;
};