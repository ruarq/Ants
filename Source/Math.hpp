#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

/**
 * @brief Get the dot product of two 2d vectors
 * @tparam T The type of the vectors
 * @param a Vector one
 * @param b Vector two
 * @return The dot product of two vectors
 */
template<typename T>
float Dot(const T &a, const T &b)
{
	return a.x * b.x + a.y * b.y;
}

/**
 * @brief Get the length of a 2d vector
 * @tparam T The type of the vectors
 * @param vec The vector
 * @return The length of the vector
 */
template<typename T>
float Length(const T &vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

/**
 * @brief Get the normalized version of a 2d vector
 * @tparam T The type of the vector
 * @param vec The vector to be normalized
 */
template<typename T>
T Normalized(const T &vec)
{
	const float length = Length(vec);
	return T(vec.x / length, vec.y / length);
}

/**
 * @brief Get the angle between to 2d vectors
 * @tparam T The type of the vectors
 * @param a Vector one
 * @param b Vector two
 * @return The angle between the two vectors in degrees
 */
template<typename T>
float Angle(const T &a, const T &b)
{
	return std::acos(Dot(a, b) / (Length(a) * Length(b))) * 180.0f / M_PI;
}

/**
 * @brief Get the rotation of a 2d vector (useful to rotate sprites)
 * @tparam T The type of the vector
 * @param vec The vector to get the rotation of
 * @return The rotation of the vector relative to the x-axis of the screen
 */
template<typename T>
float Angle(const T &vec)
{
	return std::atan2(vec.y, vec.x) * (180.0f / M_PI) + 90.0f;
}

/**
 * @brief Clamp the length of a 2d vector
 * @tparam T The type of the vector
 * @param vec The vector to be clamped
 * @return Clamped vector
 */
template<typename T>
sf::Vector2<T> Clamp(const sf::Vector2<T> &vec, const T length)
{
	if (Length(vec) > length)
	{
		return Normalized(vec) * length;
	}
	else
	{
		return vec;
	}
}
