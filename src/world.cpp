#include <porto/world.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <assert.h>
#include <porto/scene.h>
#include <porto/camera.h>

static bool debug = false; 

porto::World::World(int argc, char *argv[]) : mpi_unit{argc, argv}
{
	if (argc >= 1) {
		if(strcmp(argv[1], "-debug") == 0)
		{
			debug = true;
			return;
		}
		else
		{
			conf_file.open(argv[1]);
			if (conf_file.is_open())
				return;
		}
	}
	if (getrank()==0)
		fprintf(stderr, "Please, use\n mpirun -np 8 ./porto configs/conf.json\n");
	status = BAD_INPUT;
	//problems with paralell dialog
	/*for (;;) {
		std::cout << "\nType path to configuration file or press Ctrl + D\n>>> ";
		if (std::cin.eof()) return;
		std::string f;
		std::cin >> f;
		conf_file.open(f.c_str());
		if (conf_file.is_open())
			return;
	}*/
}

int porto::World::init()
{
	if(!debug)
	{
		read_configs(cameras, scene, conf_file);
		for (auto cam : cameras){
			engines.push_back({scene, cam});
		}
	}
	else
	{
		Scene _s();
		Raytracer _e(std::make_shared<Scene>(), std::make_shared<Camera>(90, 160, 90, 160, 90, "/dev/stdout"));
		debug_init_scene(_e);
		engines.push_back(_e);
	}
	return 0;
}


int porto::World::run()
{
	for (size_t i=0; i<engines.size(); ++i){
		mpi_unit.run(engines[i]);
		if (!debug && getrank()==0)
			fprintf(stderr, "\n\n!!!!!!!!!!!!!\nPicture #%d is Complete\n\nName is %s\n!!!!!!!!!!!!!\n\n", (int)i, engines[i].cam->getfilename().c_str());
	}
	return 0;
}

porto::World::~World(){
	conf_file.close();
}