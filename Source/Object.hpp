#pragma once

#include <SFML/Graphics.hpp>

class World;

class Object
{
public:
	virtual ~Object() = default;

public:
	virtual void Update(World &world, const float deltaTime) = 0;
	virtual void Render(sf::RenderWindow &window) = 0;

	void SetPosition(const sf::Vector2f &position);
	sf::Vector2f GetPosition() const;

protected:
	sf::Vector2f position;
};