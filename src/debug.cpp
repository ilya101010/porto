#include <porto/config_io.h>
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
#include <porto/material.h>


namespace porto
{
	void debug_init_scene(Raytracer &engine)
	{
		for(int x = -3; x <= 3; x++)	
			for(int y = -3; y<=3; y++)
			{
				if(x != 0 || y != 0)
					engine.scene->add(std::make_shared<Sphere>(Vec3(x, y, 2.5), 0.5, std::make_shared<Lambertian>(Vec3(1,0,0))));
				else
					engine.scene->add(std::make_shared<Sphere>(Vec3(0, 0, 2), 0.5, std::make_shared<SimpleDiffuseLight>(Vec3(1,1,1))));
			}

//		engine.scene->add(std::make_shared<Sphere>(Vec3(0, 0, 3.5), 1, std::make_shared<Dielectric>(0.7)));
		return;

		for(float a = 0; a<5;a++)
			for(float b = 0; b<5; b++)
			{
				engine.scene->add(std::make_shared<Sphere>(-float(-5+2*a), -float(-5+2*b), 2+(a+b)/2, 0.9f) );
			}
	}
}