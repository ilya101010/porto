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


namespace porto
{
    enum{
        OK, BAD_INPUT
    };
    class World
    {
        MPI_unit mpi_unit;
        int status = OK;
        std::vector < Raytracer >  engines;
        std::vector < std::shared_ptr < Camera > > cameras;
        std::shared_ptr < Scene > scene;
        std::ifstream conf_file;
    public:
        World(int argc, char *argv[]);
        ~World();
        int init();
        int run();
        int getstatus() const {return status;}
        int getrank() const {return mpi_unit.getrank();}
    };
}
