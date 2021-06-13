#include "ApplicationStateRunning.hpp"

ApplicationStateRunning::ApplicationStateRunning()
{
	sf::Texture antTexture;
	antTexture.loadFromFile("Resources/Ant.png");
	TextureManager::AddTexture("Ant", antTexture);

	world.AddObject(new Ant());
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