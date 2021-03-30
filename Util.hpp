#pragma once

#include <cstdlib>

#include "olcPixelGameEngine.h"

inline olc::vf2d RandomVector2D()
{
	return olc::vf2d(std::rand() % 101 - 50, std::rand() % 101 - 50).norm();
}