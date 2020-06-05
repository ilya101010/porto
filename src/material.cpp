#include <porto/material.h>
#include <porto/vec3.h>
#include <porto/ray.h>

namespace porto
{
	static float schlick(float cosine, float ref_idx) {
		float r0 = (1-ref_idx) / (1+ref_idx);
		r0 = r0*r0;
		return r0 + (1-r0)*pow((1 - cosine),5);
	}


	static bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
		Vec3 uv = normalize(v);
		float dt = dot(uv, n);
		float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
		if (discriminant > 0) {
			refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
			return true;
		}
		else
			return false;
	}

	static Vec3 reflect(const Vec3& v, const Vec3& n) {
		 return v - 2*dot(v,n)*n;
	}

	bool Lambertian::scatter
	(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 scatter_direction = rec.normal + random_unit_vector();
		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

	bool Dielectric::scatter
	(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
	{
		attenuation = Vec3(1.0, 1.0, 1.0);
		double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

		Vec3 unit_direction = normalize(r_in.dir());
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
		if (etai_over_etat * sin_theta > 1.0 ) {
			Vec3 reflected = reflect(unit_direction, rec.normal);
			scattered = Ray(rec.p, reflected);
			return true;
		}

		Vec3 refracted; refract(unit_direction, rec.normal, etai_over_etat, refracted);
		scattered = Ray(rec.p, refracted);
		return true;
	}
}