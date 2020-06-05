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
#include <porto/config_io.h>
#include <porto/world.h>
namespace p = porto;


int main(int argc, char *argv[])
{
	p::World boss(argc, argv);
	if (boss.getstatus()!= p::OK){
		return 0;
	}
	boss.init();
	boss.run();
}