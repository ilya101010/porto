#include <porto/raytracer.h>
#include <porto/utility.h>
#include <cfloat>
#include <iostream>


const float MAXF = FLT_MAX;
namespace porto
{
	static Vec3 color(const Ray &r, Scene &scene) {
		//std::cerr << "C" << r.src() << ";" << r.dir();
		HitRecord hr;
		if(scene.hit(r, 0.0001, MAXF, hr)) {
			Vec3 target = hr.p + hr.normal;// + random_in_unit_sphere();
			return 0.8 * color(Ray(hr.p, target - hr.p), scene);
		}
		else {
			Vec3 unit_direction = r.dir();
			float t = 0.5*(unit_direction.y + 1.0);
			return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
		}
		//std::cerr << "CEnd";
	}

	Raytracer::Raytracer(int width, int height, float vfov,	Vec3 origin) // todo: origin
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
			float u = float(x + random_double()) / float(width);
			float v = float(y + random_double()) / float(height);
			Ray r = cam.getRay(u, v);
			col += color(r, scene);
		}

		#ifdef DEBUG
			if(i == 0 && j % 100 == 0) std::cerr << "FUCK\n";
		#endif

		col /= float(ns);
		return col;
	}

	Raytracer::~Raytracer() {}
}