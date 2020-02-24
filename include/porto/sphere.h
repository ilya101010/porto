#pragma once
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/ihittable.h>

namespace porto
{
    class Sphere: public IHittable
    {
    public:
        Vec3 c;
        float r;

        Sphere(const Vec3 &center, float radius) : c{center}, r{radius} {}
        Sphere(float x, float y, float z, float radius) : c{x,y,z}, r{radius} {}

        virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord& record) const; 
    };
}