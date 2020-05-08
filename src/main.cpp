#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/sphere.h>
#include <porto/ihittable.h>
#include <porto/scene.h>
#include <porto/camera.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <random>
#include <cstdlib>
#include <porto/raytracer.h>
#include <cstdio>
#include <unistd.h>
#include <porto/mpi_unit.h>
namespace p = porto;

p::Sphere s(0,0,-2,1), s1(0,-100.6,-2,100);//, s2(-1,0.4,-0.7,0.7);

int main(int argc, char *argv[])
{
	//MPI
	p::MPI_unit world(argc, argv);
	const char * out_file_name = "ex.ppm";

	//TRACE
	int nx = 600;
	int ny = 600;
	p::Raytracer engine{nx, ny, 90};
	//engine.scene.add(&s);
	for(double a = 0; a<5;a++)
		for(double b = 0; b<5; b++) 
		{
			auto sph = p::Sphere(double(-5+2*a), double(-5+2*b), -2-(a+b)/2, 0.9f);
			engine.scene.add(std::make_shared<p::Sphere>(sph));
		}
	//#pragma omp parallel for
	world.run(engine, nx, ny, out_file_name);
}