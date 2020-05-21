#pragma once

#include <porto/vec3.h>
#include <porto/ray.h>
#include <memory>
// #include <porto/material.h> -- not needed

namespace porto
{
	class Material;
	struct HitRecord
	{
		double t;
		Vec3 p;
		Vec3 normal;
		std::shared_ptr<Material> mat_ptr;
		double u, v;
		bool front_face;

		inline void set_face_normal(const Ray& r, const Vec3& out_normal) {
			front_face = dot(r.dir(), out_normal) < 0;
			normal = front_face ? out_normal : -out_normal;
		}
	};

	class IHittable
	{
	public:
		virtual bool hit
			(const Ray &ray, double t_min, double t_max, HitRecord& record) const = 0;
		virtual ~IHittable() {};
	};
}