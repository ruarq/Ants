#include "World.hpp"

World::World()
	: quadtree(sf::Vector2f(1280.0f, 720.0f), 512, 8)
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

	sf::CircleShape shape;
	shape.setRadius(75.0f);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);
	window.draw(shape);
	for (Object *object : quadtree.Query(shape.getPosition(), shape.getRadius()))
	{
		shape.setRadius(1.0f);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		shape.setPosition(object->GetPosition());
		shape.setFillColor(sf::Color::Red);
		window.draw(shape);
	}
}

void World::AddObject(Object *object)
{
	spawnQueue.push_back(object);
}

std::vector<Object*> World::Query(const sf::Vector2f &point) const
{
	return quadtree.Query(point);
}

std::vector<Object*> World::Query(const sf::Vector2f &point, const float radius) const
{
	return quadtree.Query(point, radius);
}