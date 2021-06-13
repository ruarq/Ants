#include "ApplicationStateRunning.hpp"

ApplicationStateRunning::ApplicationStateRunning()
{
	world.AddObject(new Food());
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