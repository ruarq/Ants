#include "ApplicationStateRunning.hpp"

ApplicationStateRunning::ApplicationStateRunning()
{
	sf::Texture antTexture;
	antTexture.loadFromFile("Resources/Ant.png");
	TextureManager::AddTexture("Ant", antTexture);

	// Create a home
	Home *home = new Home();
	home->SetPosition(sf::Vector2f(640.0f, 360.0f));
	world.AddObject(home);

	// Create some ants
	for (std::uint32_t i = 0; i < 16; i++)
	{
		Ant *newAnt = new Ant();
		newAnt->SetPosition(sf::Vector2f(640.0f, 360.0f));
		world.AddObject(newAnt);
	}

	// Spawn some random food
	for (std::uint32_t i = 0; i < 100; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(Random(300.0f, 310.0f), Random(300.0f, 310.0f)));
		world.AddObject(newFood);
	}

	for (std::uint32_t i = 0; i < 100; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(Random(600.0f, 610.0f), Random(600.0f, 610.0f)));
		world.AddObject(newFood);
	}

	for (std::uint32_t i = 0; i < 100; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(Random(890.0f, 900.0f), Random(630.0f, 640.0f)));
		world.AddObject(newFood);
	}
}

ApplicationState* ApplicationStateRunning::Update(const float deltaTime)
{
	world.Update(deltaTime);

	return nullptr;
}

void ApplicationStateRunning::Render(sf::RenderWindow &window)
{
	world.Render(window);
}