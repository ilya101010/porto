#include <porto/sphere.h>
#include <porto/ihittable.h>


porto::Sphere* porto::Sphere::clone() const{
    return new porto::Sphere(*this);
}

bool porto::Sphere::hit
	(const Ray &ray, float t_min, float t_max, HitRecord& record) const
{
    Vec3 oc = ray.src() - c;
    float A = 1; // abs(ray.dir()) = 1
    float B = dot(oc, ray.dir());
    float C = dot(oc, oc) - r*r;
    float D = B*B - A*C; // D is actually D/4

    if (D > 0) {
    	float sqD = sqrt(D);
        float temp = (-B - sqD)/A;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - c) / r;
            return true;
        }

        temp = (-B + sqD) / A;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - c) / r;
            return true;
        }
    }

    return false;
}