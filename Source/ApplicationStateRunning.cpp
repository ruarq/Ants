#include "ApplicationStateRunning.hpp"

ApplicationStateRunning::ApplicationStateRunning()
{
	view.setSize(1280.0f, 720.0f);
	view.setCenter(0.0f, 0.0f);

	sf::Texture antTexture;
	antTexture.loadFromFile("Resources/Ant.png");
	TextureManager::AddTexture("Ant", antTexture);

	// Create a home
	Home *home = new Home();
	world.AddObject(home);

	// Create some ants
	for (std::uint32_t i = 0; i < 64; i++)
	{
		Ant *newAnt = new Ant();
		newAnt->SetPosition(home->GetPosition());
		world.AddObject(newAnt);
	}

	// Generate a food
	for (std::uint32_t i = 0; i < 512; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(200.0f, 200.0f) + RandomVec2d() * Random(0.0f, 10.0f));
		world.AddObject(newFood);
	}

	for (std::uint32_t i = 0; i < 512; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(-200.0f, 200.0f) + RandomVec2d() * Random(0.0f, 10.0f));
		world.AddObject(newFood);
	}

	for (std::uint32_t i = 0; i < 512; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(200.0f, -200.0f) + RandomVec2d() * Random(0.0f, 10.0f));
		world.AddObject(newFood);
	}

	for (std::uint32_t i = 0; i < 512; i++)
	{
		Food *newFood = new Food();
		newFood->SetPosition(sf::Vector2f(-200.0f, -200.0f) + RandomVec2d() * Random(0.0f, 10.0f));
		world.AddObject(newFood);
	}
}

ApplicationState* ApplicationStateRunning::Update(const float deltaTime)
{
	world.Update(deltaTime);

	// move view
	const float moveSpeed = 250.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		view.move(0.0f, -moveSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		view.move(-moveSpeed * deltaTime, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		view.move(0.0f, moveSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		view.move(moveSpeed * deltaTime, 0.0f);
	}

	// zoom mechanic
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
	{
		view.zoom(1.0f + deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
	{
		view.zoom(1.0f - deltaTime);
	}

	return nullptr;
}

void ApplicationStateRunning::Render(sf::RenderWindow &window)
{
	window.setView(view);
	world.Render(window);
}