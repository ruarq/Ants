#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Object.hpp"

class World final
{
public:
	~World();

public:
	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	void AddObject(Object *object);

private:
	std::vector<Object*> objects;
	std::vector<Object*> spawnQueue;
};