#include "Application.hpp"

void Application::Run()
{
	sf::Clock clock;

	window.create(sf::VideoMode(1280, 720), "Ants! Simulation - C++17 & SFML2.5.1", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	state = new ApplicationStateRunning();

	while (window.isOpen())
	{
		this->HandleEvents();

		window.clear();

		ApplicationState *newState = state->Update(clock.restart().asSeconds());
		state->Render(window);

		window.display();

		// Update the state
		if (newState)
		{
			delete state;

			state = newState;
		}
	}
}

void Application::HandleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
		}
	}
}