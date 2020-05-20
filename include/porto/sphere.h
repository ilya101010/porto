#pragma once
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/ihittable.h>
#include <porto/material.h>
#include <memory>
#include <porto/utility.h>

namespace porto
{
	class Sphere: public IHittable
	{
	public:
		Vec3 c;
		double r;
		std::shared_ptr<Material> mat_ptr;
		
		Sphere(const Vec3 &center, double radius, std::shared_ptr<Material> material_ptr) : c{center}, r{radius}, mat_ptr{material_ptr} {}
		/*Sphere(double x, double y, double z, double radius) : c{x,y,z}, r{radius}
		{
			mat_ptr = std::make_shared<Lambertian>(Vec3(random_double(),random_double(),random_double()));
		}*/

		virtual bool hit(const Ray &ray, double t_min, double t_max, HitRecord& record) const;
		virtual Sphere* clone() const;
		~Sphere() {}
	};
}