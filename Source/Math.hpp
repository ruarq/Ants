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