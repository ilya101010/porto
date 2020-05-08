#pragma once
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/ihittable.h>

namespace porto
{
	class Material {
		public:
			virtual bool scatter(
				const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered)
			const = 0;
	};

	class Lambertian : public Material {
	public:
		Lambertian(const Vec3& a) : albedo(a) {}

		virtual bool scatter(
			const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
		{
			Vec3 scatter_direction = rec.normal + random_unit_vector();
			scattered = Ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}

	private:
		Vec3 albedo;
	};

	class material
	{
	public:
		material();
		~material();
		
	};
}