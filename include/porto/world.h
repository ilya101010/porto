#pragma once
#include <json.hpp>
#include <porto/raytracer.h>
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
#include <cstdio>
#include <unistd.h>
#include <porto/mpi_unit.h>
#include <json.hpp>
#include <porto/config_io.h>
#include <vector>

/*
namespace porto
{
    class World
    {
        MPI_unit mpi_unit;
        std::vector < std::shared_ptr < Raytracer > > engines;
        std::vector < std::shared_ptr < Camera > > cameras;
        std::shared_ptr < Scene > scene;
        std::ifstream conf_file;
        World(int argc, char *argv[]);
        int init();
    };
}
*/