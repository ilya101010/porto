#include <porto/sphere.h>

bool porto::Sphere::hit(const Ray &ray)
{
    Vec3 oc = ray.src() - c;
    float a = 1; // abs(ray.dir()) = 1
    float b = 2 * dot(oc, ray.dir());
    float c = dot(oc, oc) - r*r;
    float D = b*b - 4*a*c;
    return (D > 0);
}