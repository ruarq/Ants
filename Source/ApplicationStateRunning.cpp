#include "ApplicationStateRunning.hpp"

ApplicationStateRunning::ApplicationStateRunning()
{
	sf::Texture antTexture;
	antTexture.loadFromFile("Resources/Ant.png");
	TextureManager::AddTexture("Ant", antTexture);

	// Create some ants
	for (std::uint32_t i = 0; i < 100; i++)
	{
		Ant *newAnt = new Ant();
		newAnt->SetPosition(sf::Vector2f(640.0f, 360.0f));
		world.AddObject(newAnt);
	}

	// Spawn some random food
	for (std::uint32_t i = 0; i < 1000; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(Random(100.0f, 1180.0f), Random(100.0f, 620.0f)));
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