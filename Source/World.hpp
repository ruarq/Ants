#pragma once

#include <vector>
#include <unordered_map>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "TypeId.hpp"

class World final
{
public:
	~World();

public:
	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	template<typename T>
	void AddObject(T *object)
	{
		const std::uint32_t typeId = Type<T>::Id();

		// If there is no pool for a type, add it
		if (objectPool.find(typeId) == objectPool.end())
		{
			objectPool.emplace(typeId, std::vector<Object*>());
		}

		// Add the object to the spawnQueue
		spawnQueue.push_back(std::make_pair(typeId, object));
	}

	template<typename T>
	std::vector<Object*> GetAllObjectsOfType() const
	{
		const std::uint32_t typeId = Type<T>::Id();
		if (objectPool.find(typeId) == objectPool.end())
		{
			return std::vector<Object*>();
		}

		return objectPool.at(typeId);
	}

private:
	std::unordered_map<std::uint32_t, std::vector<Object*>> objectPool;
	std::vector<std::pair<std::uint32_t, Object*>> spawnQueue;
};