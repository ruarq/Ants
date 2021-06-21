#include "World.hpp"

World::World()
	: quadtree(sf::Vector2f(1280.0f, 720.0f), 512)
{
}

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
	// Insert the spawnQueue into the objectPool
	objects.insert(objects.end(), spawnQueue.begin(), spawnQueue.end());
	spawnQueue.clear();

	quadtree.Clear();
	for (Object *object : objects)
	{
		quadtree.Insert(object);
	}

	for (auto objectItr = objects.begin(); objectItr != objects.end();)
	{
		Object *object = *objectItr;
		object->Update(*this, deltaTime);

		if (!object->IsAlive())
		{
			objectItr = objects.erase(objectItr);
			delete object;
		}
		else
		{
			objectItr++;
		}
	}
}

void World::Render(sf::RenderWindow &window)
{
	for (Object *object : objects)
	{
		object->Render(window);
	}

	#if defined(DEBUG)
	quadtree.Render(window);
	#endif
}

void World::AddObject(Object *object)
{
	spawnQueue.push_back(object);
}

std::vector<Object*> World::GetNeighbors(const Object *object) const
{
	return quadtree.GetNeighbors(object);
}

// std::vector<Object*> World::GetNeighbors(const sf::Vector2f &position) const
// {
// 	return quadtree.GetNeighbors(position);
// }