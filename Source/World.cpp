#include "World.hpp"

World::~World()
{
	for (Object *object : objects)
	{
		if (object)
		{
			delete object;
		}
	}
}

void World::Update(const float deltaTime)
{
	for (Object *object : objects)
	{
		object->Update(*this, deltaTime);
	}

	objects.insert(objects.end(), spawnQueue.begin(), spawnQueue.end());
	spawnQueue.clear();
}

void World::Render(sf::RenderWindow &window)
{
	for (Object *object : objects)
	{
		object->Render(window);
	}
}

void World::AddObject(Object *object)
{
	spawnQueue.push_back(object);
}