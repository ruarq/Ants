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
	std::vector<Object*> deadObjects;

	for (auto &elem : objectPool)
	{
		for (auto objectItr = elem.second.begin(); objectItr != elem.second.end();)
		{
			Object *object = *objectItr;
			object->Update(*this, deltaTime);

			if (!object->IsAlive())
			{
				objectItr = elem.second.erase(objectItr);
				delete object;
			}
			else
			{
				objectItr++;
			}
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