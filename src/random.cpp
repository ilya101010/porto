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

	// Vec3 random_unit_vector() {
	// 	double costheta = random_double(-1,1);
	// 	double cosphi = random_double(-1, 1);
	// 	double sintheta
	// 	auto phi = random_double(0, 2*pi);
	// 	return Vec3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));
	// }

	Vec3 random_unit_vector()
	{
		Vec3 p;
		do {
			p = 2.0f * Vec3(random_double(0, 1), random_double(0, 1), random_double(0, 1)) - Vec3(1.0f, 1.0f, 1.0f);
		} while (p.squared_length() >= 1.0f);
		return p;
	}
}