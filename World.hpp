#pragma once

#include <vector>

#include "olcPixelGameEngine.h"

class GameObject;

class World final
{
public:
	~World();

public:
	void Create(olc::PixelGameEngine &context);
	void Spawn(GameObject *gameObject);

	void Update(const float dt);
	void Render(olc::PixelGameEngine &context);

	std::vector<GameObject*> GetAllObjects() const;

private:
	std::vector<GameObject*> spawnQueue;
	std::vector<GameObject*> gameObjects;
};