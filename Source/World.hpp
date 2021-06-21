#pragma once

#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "Quadtree.hpp"

class World final
{
public:
	World();
	~World();

public:
	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	void AddObject(Object *object);
	std::vector<Object*> GetNeighbors(const Object *object) const;
	// std::vector<Object*> GetNeighbors(const sf::Vector2f &position) const;

private:
	std::vector<Object*> objects;
	std::vector<Object*> spawnQueue;

	Quadtree quadtree;
};