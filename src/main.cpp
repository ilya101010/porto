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
namespace p = porto;

using json = nlohmann::json;

int main(int argc, char *argv[])
{
	p::MPI_unit world(argc, argv);
	p::write_hard_configs();//writing hardcoded configs to conf.json
	std::vector< p::Camera> cameras;//list of cameras to make more than one picture with same scene //haven't done
	p::Scene scene;//scene to read from json
	p::read_configs(cameras, scene);//reading configs from json
	


	const char * out_file_name = "ex.ppm";//picture

	//TRACE
	//int nx = 700; 
	//int ny = 700;
	std::cout<<"\nstill alive #1\n";
	p::Raytracer engine{1, 1, 1};

	engine.scene = scene;
	engine.cam = cameras[0];


	std::cout<<scene.size()<<'\n';
	std::cout<<engine.scene.size()<<'\n';
	world.run(engine, out_file_name);
	std::cout<<"\nstill alive #2\n";
}