#include <porto/raytracer.h>
#include <porto/utility.h>
#include <porto/ray.h>
#include <iostream>
#include <porto/material.h>
#include <porto/vec3.h>

namespace porto
{
	static Vec3 color(const Ray &r, std::shared_ptr<Scene> &scene, int depth = 10) {
		if(depth == 0)
			return Vec3(0,0,0);
		HitRecord hr;
		if(scene->hit(r, 0.0001, infinity, hr)) {
			Ray scattered;
			Vec3 attenuation;
			Vec3 emitted = hr.mat_ptr->emitted(0, 0, hr.p);
			if (hr.mat_ptr->scatter(r, hr, attenuation, scattered))
				return attenuation * color(scattered, scene, depth-1) + emitted;
			else
				return emitted;
			return Vec3(0,0,0);
		}
		Vec3 unit_direction = r.dir();
		double t = 0.5*(unit_direction.y + 1.0);
		return Vec3(0.0, 0.0, 0.0);
		//return ((1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0))/10;
		//std::cerr << "CEnd";
	}

	/*Raytracer::Raytracer(int width, int height, double vfov, Vec3 origin) // todo: origin
				: cam { std::make_shared<Camera>(vfov, (double) width, (double) height, width, height, std::string("ex.ppm"))}
	{
		this->width = width;
		this->height = height;
		//cam = Camera(vfov, width, height);
	}*/
	Raytracer::Raytracer(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> cam) : width{cam->getnx()}, height{cam->getny()}
		{
			this->scene = scene;
			this->cam = cam;
		};

	Vec3 Raytracer::getPixel(int x, int y)
	{
		int ns = 400;
		Vec3 col(0, 0, 0);
		for (int s = 0; s < ns; s++) {
			double u = double(x + random_double()) / double(width);
			double v = double(y + random_double()) / double(height);
			Ray r = cam->getRay(u, v);
			//std::cout<<r.src().r<<' '<<r.src().g<<' '<<r.src().b<<' '<<r.dir().r<<' '<<r.dir().g<<' '<<r.dir().b<<'\n';
			col += color(r, scene);
		}

		#ifdef DEBUG
			if(i == 0 && j % 100 == 0) std::cerr << "FUCK\n";
		#endif

		col /= double(ns);
		return col;
	}

	Raytracer::~Raytracer() {}
}