#pragma once

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Object.hpp"

class Pheromone final : public Object
{
public:
	static constexpr float lifeTime = 45.0f;

public:
	enum Type { ToHome = 0, ToFood };

public:
	Pheromone(const Type type);

public:
	void Update(World &world, const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

	Type GetType() const;

private:
	Type type;
	sf::CircleShape shape;
	float timeAlive = 0.0f;
};