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
#include <json.hpp>
#include <porto/config_io.h>
#include <porto/world.h>
namespace p = porto;

using json = nlohmann::json;


int main(int argc, char *argv[])
{
	//p::write_hard_configs("configs/conf.json");
	//return 0;
	//you should uncomment lines above and comment lines below and (make) and run to make a configs file
	//then use another part of main
	p::World boss(argc, argv);
	if (boss.getstatus()!= p::OK){
		//if (boss.getrank()==0)
		return 0;
	}
	boss.init();
	boss.run();
}