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
	p::MPI_unit world(argc, argv);
	//if (world.getrank() == 0)
		//p::write_hard_configs();//writing hardcoded configs to conf.json
	//usleep(1000*world.getrank());
	//std::cout<<"\nconfs written\n";
	std::vector< std::shared_ptr<p::Camera> > cameras;//list of cameras to make more than one picture with same scene //haven't done
	std::shared_ptr<p::Scene> scene;//scene to read from json
	p::read_configs(cameras, scene);//reading configs from json
	
	const char * out_file_name = "ex.ppm";//picture

	//TRACE
	//int nx = 700;//we don't need it anymore  
	//int ny = 700;
	//std::cout<<"\nstill alive #1\n";
	p::Raytracer engine{scene, cameras[0]};
	//std::cout<<"\nstill alive #1_0\n";
	//engine.scene = scene;//copying is not good, fix it
	//engine.cam = cameras[0];//all would be broken if you uncommented this line, fix it
 
	//std::cout<<scene->size()<<'\n';//check that reading configs is successfull
	//std::cout<<"\nstill alive #1_1\n";
	//std::cout<<engine.scene->size()<<'\n';//I've just checked that copying is successfull
	//std::cout<<"\nstill alive #1_2\n";
	world.run(engine, out_file_name);//run one of pictures, only first camera
	//std::cout<<"\nstill alive #2\n";

	//there are promblems with paralell running cause all streams write some debug info on desctop in the same time
}