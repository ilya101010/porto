#pragma once
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/ihittable.h>
#include <cmath>

namespace porto
{
	class Material {
	public:
		virtual bool scatter(
			const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered)
		const = 0;

		virtual Vec3 emitted(float u, float v, const Vec3& p) const {
			return Vec3(0, 0, 0);
		}
	};

	class Lambertian : public Material {
	public:
		Lambertian(const Vec3& a) : albedo(a) {}

		bool scatter
		(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;

	private:
		Vec3 albedo;
	};

	class Dielectric : public Material {
    public:
        Dielectric(double ri) : ref_idx(ri) {}

        bool scatter
        (const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;

    public:
        double ref_idx;
	};

	class SimpleDiffuseLight : public Material {
	private:
		Vec3 emit;
	public:
		SimpleDiffuseLight(Vec3 a) : emit(a) {}
		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const { return false; }
		virtual Vec3 emitted(float u, float v, const Vec3& p) const { return emit; }
	};
}