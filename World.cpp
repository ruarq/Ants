#include "World.hpp"

#include "GameObject.hpp"
#include "Ant.hpp"

World::~World()
{
	// Clean up
	for (GameObject *gameObject : gameObjects)
	{
		if (gameObject)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}
}

void World::Create(olc::PixelGameEngine &context)
{
}

void World::Spawn(GameObject *gameObject)
{
	spawnQueue.push_back(gameObject);
}

void World::Update(const float dt)
{
	std::vector<GameObject*> objectsToCreate;

	// Put every game object in the spawn queue into the game object list
	for (GameObject *gameObject : spawnQueue)
	{
		gameObjects.push_back(gameObject);
		objectsToCreate.push_back(gameObject);
	}
	spawnQueue.clear();

	/**
	 * I had the problem that when I called gameObject->Create() inside the spawnQueue loop,
	 * that some game objects spawned new game objects while creating themselves, like AntHome or FoodSource.
	 * Looping over the spawnQueue while incrementing it resulted in a segmentation fault
	 */
	for (GameObject *gameObject : objectsToCreate)
	{
		gameObject->Create(*this);
	}

	// Update all game objects
	for (auto itr = gameObjects.begin(); itr != gameObjects.end();)
	{
		GameObject *gameObject = *itr;

		if (gameObject->IsAlive())
		{
			gameObject->Update(*this, dt);
			itr++;
		}
		else
		{
			itr = gameObjects.erase(itr);
		}
	}
}

void World::Render(olc::PixelGameEngine &context)
{
	for (GameObject *gameObject : gameObjects)
	{
		gameObject->Render(context);
	}
}

std::vector<GameObject*> World::GetAllObjects() const
{
	return gameObjects;
}