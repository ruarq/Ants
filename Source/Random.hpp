#pragma once

#include <random>

#include <SFML/System/Vector2.hpp>

/**
 * @brief Get a random float in the range min to max (default 0.0 - 1.0)
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 * @return A random value in the range min to max
 */
inline float Random(const float min = 0.0f, const float max = 1.0f)
{
	static std::random_device randomDevice;
	static std::mt19937 randomEngine(randomDevice());
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(randomEngine);
}

/**
 * @brief Get a random normalized 2d vector
 * @return Random normalized 2d vector
 */
inline sf::Vector2f RandomVec2d()
{
	return Normalized(sf::Vector2f(Random(-1.0f, 1.0f), Random(-1.0f, 1.0f)));
}