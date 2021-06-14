#include "World.hpp"

World::~World()
{
	for (auto &elem : objectPool)
	{
		for (Object *object : elem.second)
		{
			if (object)
			{
				delete object;
			}
		}
	}
}

void World::Update(const float deltaTime)
{
	for (auto &elem : objectPool)
	{
		for (Object *object : elem.second)
		{
			object->Update(*this, deltaTime);
		}
	}

	// Insert the spawnQueue into the objectPool
	for (auto &elem : spawnQueue)
	{
		objectPool.at(elem.first).push_back(elem.second);
	}

	spawnQueue.clear();
}

void World::Render(sf::RenderWindow &window)
{
	for (auto &elem : objectPool)
	{
		for (Object *object : elem.second)
		{
			object->Render(window);
		}
	}
}