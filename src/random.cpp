#include <porto/vec3.h>
#include <porto/random.h>
#include <random>
#include <functional>

double porto::random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<double()> rand_generator = std::bind(distribution, generator);
	return rand_generator();
}

porto::Vec3 porto::random_in_unit_sphere() {
	porto::Vec3 r;
	r = 2*Vec3(random_double(), random_double(), 0) - Vec3(1,1,1);
	r.normalize();
	r *= random_double();
	return r;
}