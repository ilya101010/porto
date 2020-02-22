#pragma once
#include <porto/vec3.h>
#include <porto/ray.h>

namespace porto
{
    class Sphere
    {
    public:
        Vec3 c;
        float r;

        Sphere(const Vec3 &center, float radius) : c{center}, r{radius} {}
        Sphere(float x, float y, float z, float radius) : c{x,y,z}, r{radius} {}

        bool hit(const Ray &ray);
    };

    bool porto::Sphere::hit(const Ray &ray)
    {
        Vec3 oc = ray.src() - c;
        float a = 1; // abs(ray.dir()) = 1
        float b = 2 * dot(oc, ray.dir());
        float c = dot(oc, oc) - r*r;
        float D = b*b - 4*a*c;
        return (D > 0);
    }
}
