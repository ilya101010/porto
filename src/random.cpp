#include <porto/utility.h>
#include <porto/vec3.h>

namespace porto
{
	double random_double(double l, double r)
	{
		static std::uniform_real_distribution<double> distribution(l, r);
		static std::mt19937 generator;
		static std::function<double()> rand_generator =
			std::bind(distribution, generator);
		return rand_generator();
	}

	Vec3 random_unit_vector() {
		auto a = random_double(0, 2*pi);
		auto z = random_double(-1, 1);
		auto r = sqrt(1 - z*z);
		return Vec3(r*cos(a), r*sin(a), z);
	}
}