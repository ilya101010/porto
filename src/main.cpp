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
	//int nx = 700;//we don't need it anymore  
	//int ny = 700;
	std::cout<<"\nstill alive #1\n";
	p::Raytracer engine{500, 500, 90};
	engine.cam.nx = 500;//crutch, it should be in constructor
	engine.cam.ny = 500;

	engine.scene = scene;//copying is not good, fix it
	//engine.cam = cameras[0];//all would be broken if you uncommented this line, fix it


	std::cout<<scene.size()<<'\n';//check that reading configs is successfull
	std::cout<<engine.scene.size()<<'\n';//I've just checked that copying is successfull
	world.run(engine, out_file_name);//run one of pictures, only first camera
	std::cout<<"\nstill alive #2\n";

	//there are promblems with paralell running cause all streams write some debug info on desctop in the same time
}