#pragma once

#include <functional>
#include <random>
#include <limits>

namespace porto
{
	const double infinity = std::numeric_limits<double>::infinity();
	const double pi = 3.1415926535897932385;

	double random_double(double l = 0, double r = 1);
}