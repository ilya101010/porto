#include <porto/sphere.h>
#include <porto/ihittable.h>

bool porto::Sphere::hit
	(const Ray &ray, double t_min, double t_max, HitRecord& record) const
{
	Vec3 oc = ray.src() - c;
	double A = 1; // abs(ray.dir()) = 1
	double B = dot(oc, ray.dir());
	double C = dot(oc, oc) - r*r;
	double D = B*B - A*C; // D is actually D/4

	if(D <= 0) return false;
	double sqD = sqrt(D);

	double t1 = (-B - sqD) / A, t2 = (-B + sqD) / A;
	if(!(t1 < t_max && t1 > t_min)
		&& !(t2 < t_max && t2 > t_min))
		return false;

	double t = 0;
	if(t1 < t_max && t1 > t_min)
		t = t1;
	else t = t2;

	record.t = t;
	record.p = ray.point_at_parameter(record.t);
	Vec3 out_normal = (record.p - c) / r;
	record.mat_ptr = mat_ptr;
	record.set_face_normal(ray, out_normal);

	return true;
}
