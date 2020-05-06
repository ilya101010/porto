#include <porto/raytracer.h>
#include <porto/utility.h>
#include <iostream>


namespace porto
{
	static Vec3 color(const Ray &r, Scene &scene) {
		//std::cerr << "C" << r.src() << ";" << r.dir();
		HitRecord hr;
		if(scene.hit(r, 0.0001, infinity, hr)) {
			Vec3 target = hr.p + hr.normal;// + random_in_unit_sphere();
			return 0.8 * color(Ray(hr.p, target - hr.p), scene);
		}
		else {
			Vec3 unit_direction = r.dir();
			double t = 0.5*(unit_direction.y + 1.0);
			return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
		}
		//std::cerr << "CEnd";
	}

	Raytracer::Raytracer(int width, int height, double vfov, Vec3 origin) // todo: origin
				: cam{vfov, width, height}
	{
		this->width = width;
		this->height = height;
		//cam = Camera(vfov, width, height);
	}

	Vec3 Raytracer::getPixel(int x, int y)
	{
		int ns = 10;
		Vec3 col(0, 0, 0);
		for (int s = 0; s < ns; s++) {
			double u = double(x + random_double()) / double(width);
			double v = double(y + random_double()) / double(height);
			Ray r = cam.getRay(u, v);
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