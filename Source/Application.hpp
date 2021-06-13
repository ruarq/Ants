#pragma once

#include <SFML/Graphics.hpp>

#include "ApplicationState.hpp"
#include "ApplicationStateRunning.hpp"

class Application final
{
public:
	void Run();

private:
	void HandleEvents();

private:
	sf::RenderWindow window;
	ApplicationState *state = nullptr;
};