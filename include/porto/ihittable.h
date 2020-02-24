#pragma once

#include <porto/vec3.h>

namespace porto
{
	struct HitRecord
	{
		float t;
		Vec3 p;
		Vec3 normal;
	};

	class IHittable
	{
	public:
		virtual bool hit
			(const Ray &ray, float t_min, float t_max, HitRecord& record) const = 0; 
	};
}