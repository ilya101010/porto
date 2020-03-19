#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/sphere.h>
#include <porto/ihittable.h>
#include <porto/scene.h>
#include <porto/camera.h>
#include <iostream>
#include <cfloat>
#include <functional>
#include <random>
#include <cstdlib>
#include <porto/raytracer.h>
namespace p = porto;

p::Sphere s(0,0,-2,1), s1(0,-100.6,-2,100);//, s2(-1,0.4,-0.7,0.7);

int main(int argc, char const *argv[])
{
	int nx = 100;
	int ny = 100;
	p::Raytracer engine{nx, ny, 90};
	//engine.scene.add(&s);
	for(float a = 0; a<5;a++)
		for(float b = 0; b<5; b++) {
			auto sph = p::Sphere(float(-5+2*a), float(-5+2*b), -2-(a+b)/2, 0.9f);
			engine.scene.add(sph);
		}
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	//#pragma omp parallel for
	for(int j = ny-1; j >= 0; j--)
	{
		for (int i = 0; i<nx; i++)
		{
			p::Vec3 col = engine.getPixel(i, j);
			int ir = int(255.99*col.r);
			int ig = int(255.99*col.g);
			int ib = int(255.99*col.b);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}