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
#include <porto/rect.h>


namespace porto
{
	void debug_init_scene(Raytracer &engine)
	{
		for(int x = -3; x <= 3; x++)	
			for(int y = -3; y<=3; y++)
			{
				if(x != 0 || y != 0)
					engine.scene->add(std::make_shared<Sphere>(Vec3(x, y, 2 + random_double()), 0.3 + random_double()*0.2, std::make_shared<Lambertian>(Vec3(random_double(),random_double(),random_double()))));
				else
				{
					for(int i = -10; i<20; i++)
					{
						Vec3 white(1,1,1);
						Vec3 colorrr(random_double(), random_double(), random_double());
						//colorrr = (0*white + colorrr) / 3;
						engine.scene->add(std::make_shared<XYRect>(-1000, 1000, -1.0 + 0.2*i, -0.9 + 0.2*i, 2.0+i*0.4, std::make_shared<SimpleDiffuseLight>(colorrr)));
					}
				}
					//engine.scene->add(std::make_shared<Sphere>(Vec3(0, 0, 2), 0.3, std::make_shared<SimpleDiffuseLight>(Vec3(1,1,1))));
			}

		engine.scene->add(std::make_shared<Sphere>(Vec3(0, 0, 1), 0.5, std::make_shared<Dielectric>(0.7)));
		return;

		for(float a = 0; a<5;a++)
			for(float b = 0; b<5; b++)
			{
				engine.scene->add(std::make_shared<Sphere>(-float(-5+2*a), -float(-5+2*b), 2+(a+b)/2, 0.9f) );
			}
	}
}