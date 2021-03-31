#pragma once

#include <random>
#include <cmath>

#include "olcPixelGameEngine.h"

constexpr float pi = 3.14159265358979323846f;

inline float RandomFloat(const float min, const float max)
{
	static std::random_device randomDevice;
	static std::mt19937 randomEngine(randomDevice());

	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(randomEngine);
}

inline olc::vf2d RandomVector2D()
{
	return olc::vf2d(RandomFloat(-50.0f, 50.0f), RandomFloat(-50.0f, 50.0f)).norm();
}

inline olc::vf2d RandomVector2D(const olc::vf2d &range)
{
	return olc::vf2d(RandomFloat(0.0f, range.x), RandomFloat(0.0f, range.y));
}

inline float Angle(const olc::vf2d a, const olc::vf2d b)
{
	// Basic formula for angle between two vectors
	return std::acos(std::abs(a.dot(b)) / (a.mag() * b.mag())) * (180.0f / pi);
}