#pragma once
#include <json.hpp>
#include <porto/raytracer.h>
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/sphere.h>
#include <porto/ihittable.h>
#include <porto/scene.h>
#include <porto/camera.h>
#include <fstream>
#include <iostream>
#include <vector>

namespace porto
{
    void write_hard_configs(const char * filename);

    void read_configs(std::vector< std::shared_ptr < porto::Camera > > &cameras, std::shared_ptr < Scene > & scene, std::istream & in);

    void debug_init_scene(Raytracer &engine);
}