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

void World::Create(olc::PixelGameEngine &context, const unsigned numAnts)
{
	for (unsigned i = 0; i < numAnts; i++)
	{
		Ant *ant = new Ant();
		ant->SetPosition(olc::vf2d(context.ScreenWidth() / 2.0f, context.ScreenHeight() / 2.0f));
		this->Spawn(ant);
	}
}

void World::Spawn(GameObject *gameObject)
{
	spawnQueue.push_back(gameObject);
}

void World::Update(const float dt)
{
	// Put every game object in the spawn queue into the game object list
	for (GameObject *gameObject : spawnQueue)
	{
		gameObjects.push_back(gameObject);
	}
	spawnQueue.clear();

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